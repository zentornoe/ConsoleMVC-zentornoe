#include "MainView.h"
#include "SampleView.h"
#include "OrderView.h"
#include "ApprovalView.h"
#include "MonitorView.h"
#include "ProductionView.h"
#include "ReleaseView.h"
#include "../controller/SampleController.h"
#include "../controller/OrderController.h"
#include "../controller/ProductionController.h"
#include <iostream>
#include <string>

MainView::MainView(SampleController& sampleCtrl,
                   OrderController& orderCtrl,
                   ProductionController& productionCtrl)
    : m_sampleCtrl(sampleCtrl)
    , m_orderCtrl(orderCtrl)
    , m_productionCtrl(productionCtrl)
{}

void MainView::run() {
    SampleView     sampleView(m_sampleCtrl);
    OrderView      orderView(m_orderCtrl, m_sampleCtrl);
    ApprovalView   approvalView(m_orderCtrl);
    MonitorView    monitorView(m_orderCtrl, m_sampleCtrl);
    ProductionView productionView(m_productionCtrl);
    ReleaseView    releaseView(m_orderCtrl, m_sampleCtrl);

    while (true) {
        printHeader();
        printSystemStatus();
        printMenu();

        int choice = readMenuChoice();
        switch (choice) {
            case 1: sampleView.run();     break;
            case 2: orderView.run();      break;
            case 3: approvalView.run();   break;
            case 4: monitorView.run();    break;
            case 5: productionView.run(); break;
            case 6: releaseView.run();    break;
            case 0:
                std::cout << "\n프로그램을 종료합니다.\n";
                return;
            default:
                std::cout << "잘못된 입력입니다. 다시 선택해 주세요.\n";
        }
    }
}

void MainView::printHeader() const {
    std::cout << "\n========================================\n";
    std::cout << "   S-Semi 반도체 시료 생산주문관리 시스템\n";
    std::cout << "========================================\n";
}

void MainView::printSystemStatus() const {
    int sampleCount = static_cast<int>(m_sampleCtrl.getAllSamples().size());
    int totalStock = 0;
    for (const auto& s : m_sampleCtrl.getAllSamples()) totalStock += s.getStock();

    int totalOrders = static_cast<int>(m_orderCtrl.getAllOrders().size());
    int producingCount = m_orderCtrl.countByStatus(OrderStatus::PRODUCING);

    std::cout << "[ 시스템 현황 ]\n";
    std::cout << "  등록 시료: " << sampleCount << "종"
              << "  |  총 재고: " << totalStock << "ea"
              << "  |  전체 주문: " << totalOrders << "건"
              << "  |  생산라인 대기: " << producingCount << "건\n";
    std::cout << "----------------------------------------\n";
}

void MainView::printMenu() const {
    std::cout << "  1. 시료 관리\n";
    std::cout << "  2. 시료 주문\n";
    std::cout << "  3. 주문 승인/거절\n";
    std::cout << "  4. 모니터링\n";
    std::cout << "  5. 생산라인 조회\n";
    std::cout << "  6. 출고 처리\n";
    std::cout << "  0. 종료\n";
    std::cout << "----------------------------------------\n";
    std::cout << "선택 > ";
}

int MainView::readMenuChoice() const {
    int choice = -1;
    std::cin >> choice;
    std::cin.ignore();
    return choice;
}
