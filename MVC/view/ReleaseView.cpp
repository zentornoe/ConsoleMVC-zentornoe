#include "ReleaseView.h"
#include "../controller/OrderController.h"
#include "../controller/SampleController.h"
#include "../controller/ReleaseController.h"
#include <iostream>
#include <iomanip>
#include <string>

ReleaseView::ReleaseView(OrderController& orderCtrl, SampleController& sampleCtrl)
    : m_orderCtrl(orderCtrl)
    , m_sampleCtrl(sampleCtrl)
{}

void ReleaseView::run() {
    while (true) {
        std::cout << "\n===== 출고 처리 =====\n";
        printConfirmedOrders();

        std::cout << "\n  1. 출고 처리\n";
        std::cout << "  0. 뒤로\n";
        std::cout << "선택 > ";

        int choice = -1;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: handleRelease(); break;
            case 0: return;
            default: std::cout << "잘못된 입력입니다.\n";
        }
    }
}

void ReleaseView::printConfirmedOrders() const {
    std::cout << "[ 출고 대기 주문 (CONFIRMED) ]\n";

    std::vector<const Order*> confirmed;
    for (const auto& o : m_orderCtrl.getAllOrders()) {
        if (o.getStatus() == OrderStatus::CONFIRMED)
            confirmed.push_back(&o);
    }

    if (confirmed.empty()) {
        std::cout << "  출고 대기 주문이 없습니다.\n";
        return;
    }

    std::cout << std::left
              << std::setw(22) << "주문번호"
              << std::setw(12) << "시료 ID"
              << std::setw(16) << "고객명"
              << std::setw(10) << "수량"
              << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto* o : confirmed) {
        std::cout << std::left
                  << std::setw(22) << o->getOrderId()
                  << std::setw(12) << o->getSampleId()
                  << std::setw(16) << o->getCustomerName()
                  << std::setw(10) << o->getQuantity()
                  << "\n";
    }
}

void ReleaseView::handleRelease() {
    std::cout << "출고할 주문번호: ";
    std::string orderId;
    std::getline(std::cin, orderId);

    ReleaseController releaseCtrl(m_orderCtrl);
    auto result = releaseCtrl.release(orderId);

    if (result.success) {
        std::cout << "\n출고 완료!\n";
        std::cout << "주문번호: " << result.orderId << "\n";
        std::cout << "출고수량: " << result.quantity << "ea\n";
        std::cout << "처리일시: " << result.releasedAt << "\n";
    } else {
        std::cout << "출고 실패. 주문번호를 확인해 주세요.\n";
    }
}
