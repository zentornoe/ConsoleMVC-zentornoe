#pragma once

class OrderController;
class SampleController;

class OrderView {
public:
    OrderView(OrderController& orderCtrl, SampleController& sampleCtrl);
    void run();

private:
    void handleCreateOrder();

    OrderController&  m_orderCtrl;
    SampleController& m_sampleCtrl;
};
