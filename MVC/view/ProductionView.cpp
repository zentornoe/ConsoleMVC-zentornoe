#include "ProductionView.h"
#include "../controller/ProductionController.h"
#include "../controller/OrderController.h"
#include <iostream>
#include <iomanip>
#include <queue>

// ProductionView는 생산 완료 처리를 위해 OrderController가 필요하므로
// 외부에서 완료 처리 시 OrderController를 통해 상태 변경
// 여기서는 조회만 담당

ProductionView::ProductionView(ProductionController& ctrl) : m_ctrl(ctrl) {}

void ProductionView::run() {
    while (true) {
        std::cout << "\n===== 생산라인 조회 =====\n";
        printCurrentItem();
        std::cout << "\n";
        printWaitingQueue();

        std::cout << "\n  1. 생산 완료 처리\n";
        std::cout << "  0. 뒤로\n";
        std::cout << "선택 > ";

        int choice = -1;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: handleComplete(); break;
            case 0: return;
            default: std::cout << "잘못된 입력입니다.\n";
        }
    }
}

void ProductionView::printCurrentItem() const {
    const ProductionItem* item = m_ctrl.getCurrentItem();
    std::cout << "[ 현재 처리 중 ]\n";
    if (!item) {
        std::cout << "  처리 중인 항목 없음\n";
        return;
    }
    std::cout << "  주문번호  : " << item->orderId << "\n";
    std::cout << "  시료명    : " << item->sampleName << "\n";
    std::cout << "  주문수량  : " << item->orderQuantity << "ea\n";
    std::cout << "  부족분    : " << item->shortage << "ea\n";
    std::cout << "  실생산량  : " << item->actualProduction << "ea\n";
    std::cout << "  총생산시간: " << item->totalProductionMinutes << "분\n";
}

void ProductionView::printWaitingQueue() const {
    auto queue = m_ctrl.getWaitingQueue();
    std::cout << "[ 대기 큐 (" << queue.size() << "건) ]\n";
    if (queue.empty()) {
        std::cout << "  대기 중인 항목 없음\n";
        return;
    }

    std::cout << std::left
              << std::setw(4)  << "순서"
              << std::setw(22) << "주문번호"
              << std::setw(20) << "시료명"
              << std::setw(10) << "주문량"
              << std::setw(10) << "부족분"
              << std::setw(10) << "실생산량"
              << "\n";
    std::cout << std::string(76, '-') << "\n";

    int seq = 1;
    while (!queue.empty()) {
        const auto& item = queue.front();
        std::cout << std::left
                  << std::setw(4)  << seq++
                  << std::setw(22) << item.orderId
                  << std::setw(20) << item.sampleName
                  << std::setw(10) << item.orderQuantity
                  << std::setw(10) << item.shortage
                  << std::setw(10) << item.actualProduction
                  << "\n";
        queue.pop();
    }
}

void ProductionView::handleComplete() {
    if (!m_ctrl.getCurrentItem()) {
        std::cout << "처리 중인 생산 항목이 없습니다.\n";
        return;
    }

    std::cout << "현재 항목 생산 완료 처리하시겠습니까? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        // OrderController 없이 생산 완료 처리를 위해
        // 실제 구현 시 OrderController 주입 필요
        // 여기서는 TODO 표시
        std::cout << "[TODO] OrderController를 통해 PRODUCING → CONFIRMED 전환 필요\n";
        std::cout << "       ProductionController::completeCurrentItem(callback) 호출\n";
    }
}
