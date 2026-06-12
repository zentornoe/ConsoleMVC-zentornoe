#include "ProductionLine.h"
#include <cmath>

bool ProductionLine::isEmpty() const {
    return !m_current.has_value() && m_waitingQueue.empty();
}

bool ProductionLine::isProcessing() const {
    return m_current.has_value();
}

void ProductionLine::enqueue(const ProductionItem& item) {
    m_waitingQueue.push(item);
    startNextIfIdle();
}

const ProductionItem* ProductionLine::getCurrentItem() const {
    if (!m_current.has_value()) return nullptr;
    return &m_current.value();
}

void ProductionLine::completeCurrentItem() {
    m_current.reset();
    startNextIfIdle();
}

void ProductionLine::startNextIfIdle() {
    if (!m_current.has_value() && !m_waitingQueue.empty()) {
        m_current = m_waitingQueue.front();
        m_waitingQueue.pop();
    }
}

int ProductionLine::calcActualProduction(int shortage, double yieldRate) {
    if (yieldRate <= 0.0) return shortage;
    return static_cast<int>(std::ceil(static_cast<double>(shortage) / (yieldRate * 0.9)));
}

double ProductionLine::calcTotalProductionMinutes(double avgTime, int actualProduction) {
    return avgTime * actualProduction;
}
