#pragma once
#include <string>

class Sample {
public:
    Sample() = default;
    Sample(std::string id, std::string name, double avgProductionTime, double yieldRate, int stock);

    const std::string& getId() const { return m_id; }
    const std::string& getName() const { return m_name; }
    double getAvgProductionTime() const { return m_avgProductionTime; }
    double getYieldRate() const { return m_yieldRate; }
    int getStock() const { return m_stock; }

    void setName(const std::string& name) { m_name = name; }
    void setAvgProductionTime(double t) { m_avgProductionTime = t; }
    void setYieldRate(double r) { m_yieldRate = r; }
    void setStock(int s) { m_stock = s; }
    void addStock(int amount);
    bool reduceStock(int amount);

private:
    std::string m_id;
    std::string m_name;
    double m_avgProductionTime{ 0.0 };
    double m_yieldRate{ 1.0 };
    int m_stock{ 0 };
};
