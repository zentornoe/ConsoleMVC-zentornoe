#pragma once
#include "../model/Order.h"
#include <vector>
#include <string>

class SampleController;
class ProductionController;

class OrderController {
public:
    OrderController(SampleController& sampleCtrl, ProductionController& productionCtrl);

    // 주문 접수 (RESERVED 생성). 시료 ID가 없으면 false 반환
    bool createOrder(const std::string& sampleId,
                     const std::string& customerName, int quantity);

    // RESERVED 상태 주문 목록
    std::vector<const Order*> getReservedOrders() const;

    // 모든 주문 목록
    const std::vector<Order>& getAllOrders() const;

    // 주문 ID로 조회
    Order* findById(const std::string& orderId);
    const Order* findById(const std::string& orderId) const;

    // 상태별 주문 건수 (REJECTED 제외 가능)
    int countByStatus(OrderStatus status) const;

    // 승인 처리:
    //   - 재고 >= 수량 → CONFIRMED
    //   - 재고 <  수량 → 생산라인 등록 → PRODUCING
    bool approveOrder(const std::string& orderId);

    // 거절 처리: RESERVED → REJECTED
    bool rejectOrder(const std::string& orderId);

    // 출고 처리: CONFIRMED → RELEASE
    bool releaseOrder(const std::string& orderId);

    // 주문번호 형식: ORD-YYYYMMDD-NNNN
    std::string generateOrderId() const;

    // 현재 날짜시간 문자열 (YYYY-MM-DD HH:MM:SS)
    static std::string currentDateTimeStr();

private:
    std::vector<Order> m_orders;
    SampleController& m_sampleCtrl;
    ProductionController& m_productionCtrl;
    mutable int m_dailySeq{ 0 };
    mutable std::string m_lastDate;
};
