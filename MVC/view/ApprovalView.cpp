#include "ApprovalView.h"
#include "../controller/OrderController.h"
#include <iostream>
#include <iomanip>
#include <string>

ApprovalView::ApprovalView(OrderController& orderCtrl) : m_orderCtrl(orderCtrl) {}

void ApprovalView::run() {
    while (true) {
        std::cout << "\n===== 주문 승인/거절 =====\n";
        printReservedOrders();

        std::cout << "  1. 승인\n";
        std::cout << "  2. 거절\n";
        std::cout << "  0. 뒤로\n";
        std::cout << "선택 > ";

        int choice = -1;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: handleApprove(); break;
            case 2: handleReject();  break;
            case 0: return;
            default: std::cout << "잘못된 입력입니다.\n";
        }
    }
}

void ApprovalView::printReservedOrders() const {
    auto orders = m_orderCtrl.getReservedOrders();
    if (orders.empty()) {
        std::cout << "대기 중인 주문이 없습니다.\n";
        return;
    }

    std::cout << std::left
              << std::setw(22) << "주문번호"
              << std::setw(12) << "시료 ID"
              << std::setw(16) << "고객명"
              << std::setw(10) << "수량"
              << std::setw(20) << "접수일시"
              << "\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto* o : orders) {
        std::cout << std::left
                  << std::setw(22) << o->getOrderId()
                  << std::setw(12) << o->getSampleId()
                  << std::setw(16) << o->getCustomerName()
                  << std::setw(10) << o->getQuantity()
                  << std::setw(20) << o->getCreatedAt()
                  << "\n";
    }
}

void ApprovalView::handleApprove() {
    std::cout << "승인할 주문번호: ";
    std::string orderId;
    std::getline(std::cin, orderId);

    if (m_orderCtrl.approveOrder(orderId)) {
        const Order* o = m_orderCtrl.findById(orderId);
        std::string status = o ? Order::statusToString(o->getStatus()) : "";
        std::cout << "승인 완료. 상태: " << status << "\n";
        if (o && o->getStatus() == OrderStatus::PRODUCING)
            std::cout << "(재고 부족 → 생산라인에 등록되었습니다)\n";
    } else {
        std::cout << "승인 실패. 주문번호를 확인해 주세요.\n";
    }
}

void ApprovalView::handleReject() {
    std::cout << "거절할 주문번호: ";
    std::string orderId;
    std::getline(std::cin, orderId);

    if (m_orderCtrl.rejectOrder(orderId)) {
        std::cout << "거절 완료. 상태: REJECTED\n";
    } else {
        std::cout << "거절 실패. 주문번호를 확인해 주세요.\n";
    }
}
