#pragma once

class OrderController;

class ApprovalView {
public:
    explicit ApprovalView(OrderController& orderCtrl);
    void run();

private:
    void printReservedOrders() const;
    void handleApprove();
    void handleReject();

    OrderController& m_orderCtrl;
};
