#pragma once
#include "../model/Order.h"
#include <vector>
#include <string>

class OrderController;

class ReleaseController {
public:
	explicit ReleaseController(OrderController& orderCtrl);

	// CONFIRMED 상태 주문 목록 조회
	std::vector<const Order*> getConfirmedOrders() const;

	// 출고 처리: CONFIRMED → RELEASE
	// 성공 시 출고 정보(주문번호, 수량, 일시) 반환 구조체
	struct ReleaseResult {
		bool success{ false };
		std::string orderId;
		int quantity{ 0 };
		std::string releasedAt;
	};
	ReleaseResult release(const std::string& orderId);

private:
	OrderController& m_orderCtrl;
};
