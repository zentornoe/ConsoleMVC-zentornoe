#include "OrderController.h"
#include "SampleController.h"
#include "ProductionController.h"
#include <algorithm>
#include <chrono>
#include <format>

OrderController::OrderController(SampleController& sampleCtrl, ProductionController& productionCtrl)
    : m_sampleCtrl(sampleCtrl)
    , m_productionCtrl(productionCtrl)
{}

bool OrderController::createOrder(const std::string& sampleId,
                                   const std::string& customerName, int quantity) {
    if (!m_sampleCtrl.findById(sampleId)) return false;

    std::string orderId = generateOrderId();
    std::string now = currentDateTimeStr();
    m_orders.emplace_back(orderId, sampleId, customerName, quantity, now);
    return true;
}

std::vector<const Order*> OrderController::getReservedOrders() const {
    std::vector<const Order*> result;
    for (const auto& o : m_orders) {
        if (o.getStatus() == OrderStatus::RESERVED)
            result.push_back(&o);
    }
    return result;
}

const std::vector<Order>& OrderController::getAllOrders() const {
    return m_orders;
}

Order* OrderController::findById(const std::string& orderId) {
    for (auto& o : m_orders) {
        if (o.getOrderId() == orderId) return &o;
    }
    return nullptr;
}

const Order* OrderController::findById(const std::string& orderId) const {
    for (const auto& o : m_orders) {
        if (o.getOrderId() == orderId) return &o;
    }
    return nullptr;
}

int OrderController::countByStatus(OrderStatus status) const {
    return static_cast<int>(
        std::count_if(m_orders.begin(), m_orders.end(),
            [status](const Order& o) { return o.getStatus() == status; })
    );
}

bool OrderController::approveOrder(const std::string& orderId) {
    Order* order = findById(orderId);
    if (!order || order->getStatus() != OrderStatus::RESERVED) return false;

    const Sample* sample = m_sampleCtrl.findById(order->getSampleId());
    if (!sample) return false;

    std::string now = currentDateTimeStr();

    if (sample->getStock() >= order->getQuantity()) {
        // 재고 충분 → 즉시 CONFIRMED
        m_sampleCtrl.reduceStock(order->getSampleId(), order->getQuantity());
        order->setStatus(OrderStatus::CONFIRMED);
        order->setUpdatedAt(now);
    } else {
        // 재고 부족 → 생산라인 등록 후 PRODUCING
        m_productionCtrl.enqueue(*order, sample->getName(),
                                  sample->getAvgProductionTime(), sample->getYieldRate());
        order->setStatus(OrderStatus::PRODUCING);
        order->setUpdatedAt(now);
    }
    return true;
}

bool OrderController::rejectOrder(const std::string& orderId) {
    Order* order = findById(orderId);
    if (!order || order->getStatus() != OrderStatus::RESERVED) return false;

    order->setStatus(OrderStatus::REJECTED);
    order->setUpdatedAt(currentDateTimeStr());
    return true;
}

bool OrderController::releaseOrder(const std::string& orderId) {
    Order* order = findById(orderId);
    if (!order || order->getStatus() != OrderStatus::CONFIRMED) return false;

    std::string now = currentDateTimeStr();
    order->setStatus(OrderStatus::RELEASE);
    order->setUpdatedAt(now);
    order->setReleasedAt(now);
    return true;
}

std::string OrderController::generateOrderId() const {
    auto now = std::chrono::system_clock::now();
    auto today = std::format("{:%Y%m%d}", now);

    if (today != m_lastDate) {
        m_lastDate = today;
        m_dailySeq = 0;
    }
    ++m_dailySeq;
    return std::format("ORD-{}-{:04d}", today, m_dailySeq);
}

std::string OrderController::currentDateTimeStr() {
    auto now = std::chrono::system_clock::now();
    return std::format("{:%Y-%m-%d %H:%M:%S}", now);
}
