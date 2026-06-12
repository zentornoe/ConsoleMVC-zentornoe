#pragma once

class SampleController;

class SampleView {
public:
    explicit SampleView(SampleController& ctrl);
    void run();

private:
    void printMenu() const;
    void handleRegister();
    void handleList() const;
    void handleSearch() const;

    SampleController& m_ctrl;
};
