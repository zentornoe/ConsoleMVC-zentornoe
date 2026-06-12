#include "OrderView.h"
#include "../controller/OrderController.h"
#include "../controller/SampleController.h"
#include <iostream>
#include <string>

OrderView::OrderView(OrderController& orderCtrl, SampleController& sampleCtrl)
    : m_orderCtrl(orderCtrl)
    , m_sampleCtrl(sampleCtrl)
{}

void OrderView::run() {
    handleCreateOrder();
}

void OrderView::handleCreateOrder() {
    std::cout << "\n===== 시료 주문 접수 =====\n";

    // 시료 목록 출력
    const auto& samples = m_sampleCtrl.getAllSamples();
    if (samples.empty()) {
        std::cout << "등록된 시료가 없습니다. 시료를 먼저 등록해 주세요.\n";
        return;
    }

    std::cout << "[ 등록 시료 목록 ]\n";
    for (const auto& s : samples) {
        std::cout << "  " << s.getId() << " - " << s.getName()
                  << " (재고: " << s.getStock() << "ea)\n";
    }

    std::string sampleId, customerName;
    int quantity = 0;

    std::cout << "\n시료 ID: ";
    std::getline(std::cin, sampleId);
    std::cout << "고객명: ";
    std::getline(std::cin, customerName);
    std::cout << "주문 수량 (ea): ";
    std::cin >> quantity;
    std::cin.ignore();

    if (m_orderCtrl.createOrder(sampleId, customerName, quantity)) {
        const auto& orders = m_orderCtrl.getAllOrders();
        std::cout << "\n주문 접수 완료!\n";
        std::cout << "주문번호: " << orders.back().getOrderId() << "\n";
        std::cout << "상태: RESERVED\n";
    } else {
        std::cout << "주문 접수 실패. 시료 ID를 확인해 주세요.\n";
    }
}
