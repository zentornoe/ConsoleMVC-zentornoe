#pragma once
#include "../model/ProductionLine.h"
#include "../model/Order.h"
#include <string>
#include <functional>

class SampleController;

class ProductionController {
public:
    explicit ProductionController(SampleController& sampleCtrl);

    // 생산라인에 주문 등록 (PRODUCING 전환 후 호출)
    void enqueue(const Order& order, const std::string& sampleName,
                 double avgProductionTime, double yieldRate);

    // 현재 처리 중인 항목 조회
    const ProductionItem* getCurrentItem() const;

    // 대기 큐 조회
    std::queue<ProductionItem> getWaitingQueue() const;

    // 대기 큐 크기
    int getWaitingCount() const;

    // 생산 완료 처리: 재고 추가 후 콜백으로 CONFIRMED 전환 요청
    // onComplete(orderId) 콜백이 Order 상태 변경을 담당
    void completeCurrentItem(std::function<void(const std::string& orderId)> onComplete);

    bool isEmpty() const;

private:
    ProductionLine m_line;
    SampleController& m_sampleCtrl;
};
