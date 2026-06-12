#include "MonitorView.h"
#include "../controller/OrderController.h"
#include "../controller/SampleController.h"
#include <iostream>
#include <iomanip>

MonitorView::MonitorView(OrderController& orderCtrl, SampleController& sampleCtrl)
    : m_orderCtrl(orderCtrl)
    , m_sampleCtrl(sampleCtrl)
{}

void MonitorView::run() {
    std::cout << "\n===== 모니터링 =====\n";
    printOrderStatus();
    std::cout << "\n";
    printStockStatus();

    std::cout << "\n계속하려면 Enter를 누르세요...";
    std::cin.ignore();
}

void MonitorView::printOrderStatus() const {
    std::cout << "[ 주문량 현황 (REJECTED 제외) ]\n";
    std::cout << std::left
              << std::setw(14) << "RESERVED"
              << std::setw(14) << "CONFIRMED"
              << std::setw(14) << "PRODUCING"
              << std::setw(14) << "RELEASE"
              << "\n";
    std::cout << std::string(56, '-') << "\n";
    std::cout << std::left
              << std::setw(14) << m_orderCtrl.countByStatus(OrderStatus::RESERVED)
              << std::setw(14) << m_orderCtrl.countByStatus(OrderStatus::CONFIRMED)
              << std::setw(14) << m_orderCtrl.countByStatus(OrderStatus::PRODUCING)
              << std::setw(14) << m_orderCtrl.countByStatus(OrderStatus::RELEASE)
              << "\n";
}

void MonitorView::printStockStatus() const {
    std::cout << "[ 시료별 재고 현황 ]\n";
    const auto& samples = m_sampleCtrl.getAllSamples();
    if (samples.empty()) {
        std::cout << "등록된 시료가 없습니다.\n";
        return;
    }

    // 시료별 PRODUCING + CONFIRMED 주문 수량 합산
    auto orderedQty = [&](const std::string& sampleId) {
        int total = 0;
        for (const auto& o : m_orderCtrl.getAllOrders()) {
            if (o.getSampleId() == sampleId &&
               (o.getStatus() == OrderStatus::CONFIRMED ||
                o.getStatus() == OrderStatus::PRODUCING)) {
                total += o.getQuantity();
            }
        }
        return total;
    };

    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(24) << "이름"
              << std::setw(10) << "재고(ea)"
              << std::setw(12) << "주문수량"
              << std::setw(10) << "상태"
              << "\n";
    std::cout << std::string(64, '-') << "\n";

    for (const auto& s : samples) {
        int ordered = orderedQty(s.getId());
        std::string statusStr;
        if (s.getStock() == 0)
            statusStr = "고갈";
        else if (s.getStock() < ordered)
            statusStr = "부족";
        else
            statusStr = "여유";

        std::cout << std::left
                  << std::setw(8)  << s.getId()
                  << std::setw(24) << s.getName()
                  << std::setw(10) << s.getStock()
                  << std::setw(12) << ordered
                  << std::setw(10) << statusStr
                  << "\n";
    }
}
