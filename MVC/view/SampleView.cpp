#include "SampleView.h"
#include "../controller/SampleController.h"
#include <iostream>
#include <iomanip>
#include <string>

SampleView::SampleView(SampleController& ctrl) : m_ctrl(ctrl) {}

void SampleView::run() {
    while (true) {
        std::cout << "\n===== 시료 관리 =====\n";
        printMenu();

        int choice = -1;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: handleRegister(); break;
            case 2: handleList();     break;
            case 3: handleSearch();   break;
            case 0: return;
            default: std::cout << "잘못된 입력입니다.\n";
        }
    }
}

void SampleView::printMenu() const {
    std::cout << "  1. 시료 등록\n";
    std::cout << "  2. 시료 목록 조회\n";
    std::cout << "  3. 시료 검색\n";
    std::cout << "  0. 뒤로\n";
    std::cout << "선택 > ";
}

void SampleView::handleRegister() {
    std::cout << "\n--- 시료 등록 ---\n";

    std::string name;
    double avgTime, yieldRate;
    int stock;

    std::cout << "시료명: ";
    std::getline(std::cin, name);
    std::cout << "평균 생산시간 (min/ea): ";
    std::cin >> avgTime;
    std::cout << "수율 (예: 0.92): ";
    std::cin >> yieldRate;
    std::cout << "초기 재고 (ea): ";
    std::cin >> stock;
    std::cin.ignore();

    if (m_ctrl.addSample(name, avgTime, yieldRate, stock)) {
        const auto& samples = m_ctrl.getAllSamples();
        std::cout << "등록 완료. ID: " << samples.back().getId() << "\n";
    } else {
        std::cout << "등록 실패.\n";
    }
}

void SampleView::handleList() const {
    std::cout << "\n--- 시료 목록 ---\n";
    const auto& samples = m_ctrl.getAllSamples();
    if (samples.empty()) {
        std::cout << "등록된 시료가 없습니다.\n";
        return;
    }

    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(24) << "이름"
              << std::setw(16) << "생산시간(min)"
              << std::setw(10) << "수율"
              << std::setw(10) << "재고(ea)"
              << "\n";
    std::cout << std::string(68, '-') << "\n";

    for (const auto& s : samples) {
        std::cout << std::left
                  << std::setw(8)  << s.getId()
                  << std::setw(24) << s.getName()
                  << std::setw(16) << s.getAvgProductionTime()
                  << std::setw(10) << s.getYieldRate()
                  << std::setw(10) << s.getStock()
                  << "\n";
    }
}

void SampleView::handleSearch() const {
    std::cout << "\n--- 시료 검색 ---\n";
    std::cout << "검색 키워드: ";
    std::string keyword;
    std::getline(std::cin, keyword);

    auto results = m_ctrl.searchByName(keyword);
    if (results.empty()) {
        std::cout << "검색 결과가 없습니다.\n";
        return;
    }

    std::cout << "검색 결과 " << results.size() << "건:\n";
    for (const auto* s : results) {
        std::cout << "  [" << s->getId() << "] " << s->getName()
                  << "  재고: " << s->getStock() << "ea\n";
    }
}
