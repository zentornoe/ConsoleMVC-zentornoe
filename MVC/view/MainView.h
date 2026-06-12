#pragma once

class SampleController;
class OrderController;
class ProductionController;

class MainView {
public:
    MainView(SampleController& sampleCtrl,
             OrderController& orderCtrl,
             ProductionController& productionCtrl);

    // 메인 루프 실행
    void run();

private:
    void printHeader() const;
    void printSystemStatus() const;
    void printMenu() const;
    int  readMenuChoice() const;

    SampleController&    m_sampleCtrl;
    OrderController&     m_orderCtrl;
    ProductionController& m_productionCtrl;
};
