#include "ReleaseController.h"
#include "OrderController.h"

ReleaseController::ReleaseController(OrderController& orderCtrl)
    : m_orderCtrl(orderCtrl)
{}

std::vector<const Order*> ReleaseController::getConfirmedOrders() const {
    std::vector<const Order*> result;
    for (const auto& o : m_orderCtrl.getAllOrders()) {
        if (o.getStatus() == OrderStatus::CONFIRMED)
            result.push_back(&o);
    }
    return result;
}

ReleaseController::ReleaseResult ReleaseController::release(const std::string& orderId) {
    ReleaseResult result;
    const Order* order = m_orderCtrl.findById(orderId);
    if (!order || order->getStatus() != OrderStatus::CONFIRMED) {
        return result;
    }

    int qty = order->getQuantity();
    if (!m_orderCtrl.releaseOrder(orderId)) return result;

    const Order* updated = m_orderCtrl.findById(orderId);
    result.success = true;
    result.orderId = orderId;
    result.quantity = qty;
    result.releasedAt = updated ? updated->getReleasedAt() : "";
    return result;
}
