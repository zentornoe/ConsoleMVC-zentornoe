#pragma once
#include <string>
#include <queue>
#include <optional>

struct ProductionItem {
    std::string orderId;
    std::string sampleId;
    std::string sampleName;
    int orderQuantity{ 0 };
    int shortage{ 0 };
    int actualProduction{ 0 };
    double totalProductionMinutes{ 0.0 };
    std::string estimatedCompletion;
};

class ProductionLine {
public:
    bool isEmpty() const;
    bool isProcessing() const;

    void enqueue(const ProductionItem& item);
    const ProductionItem* getCurrentItem() const;
    std::queue<ProductionItem> getWaitingQueue() const { return m_waitingQueue; }

    void completeCurrentItem();

    // 생산 수량 계산: ceil(부족분 / (수율 × 0.9))
    static int calcActualProduction(int shortage, double yieldRate);
    // 총 생산 시간: 평균생산시간 × 실생산량
    static double calcTotalProductionMinutes(double avgTime, int actualProduction);

private:
    void startNextIfIdle();

    std::optional<ProductionItem> m_current;
    std::queue<ProductionItem> m_waitingQueue;
};
