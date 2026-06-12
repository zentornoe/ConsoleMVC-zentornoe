#include "Sample.h"

Sample::Sample(std::string id, std::string name, double avgProductionTime, double yieldRate, int stock)
    : m_id(std::move(id))
    , m_name(std::move(name))
    , m_avgProductionTime(avgProductionTime)
    , m_yieldRate(yieldRate)
    , m_stock(stock)
{}

void Sample::addStock(int amount) {
    m_stock += amount;
}

bool Sample::reduceStock(int amount) {
    if (m_stock < amount) return false;
    m_stock -= amount;
    return true;
}
