#pragma once

class ProductionController;

class ProductionView {
public:
    explicit ProductionView(ProductionController& ctrl);
    void run();

private:
    void printCurrentItem() const;
    void printWaitingQueue() const;
    void handleComplete();

    ProductionController& m_ctrl;
};
