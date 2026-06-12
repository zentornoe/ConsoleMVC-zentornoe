#pragma once

class OrderController;
class SampleController;

class MonitorView {
public:
    MonitorView(OrderController& orderCtrl, SampleController& sampleCtrl);
    void run();

private:
    void printOrderStatus() const;
    void printStockStatus() const;

    OrderController&  m_orderCtrl;
    SampleController& m_sampleCtrl;
};
