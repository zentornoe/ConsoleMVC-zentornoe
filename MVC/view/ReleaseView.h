#pragma once

class OrderController;
class SampleController;

class ReleaseView {
public:
    ReleaseView(OrderController& orderCtrl, SampleController& sampleCtrl);
    void run();

private:
    void printConfirmedOrders() const;
    void handleRelease();

    OrderController&  m_orderCtrl;
    SampleController& m_sampleCtrl;
};
