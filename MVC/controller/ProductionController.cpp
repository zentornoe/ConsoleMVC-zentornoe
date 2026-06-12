#include "ProductionController.h"
#include "SampleController.h"

ProductionController::ProductionController(SampleController& sampleCtrl)
    : m_sampleCtrl(sampleCtrl)
{}

void ProductionController::enqueue(const Order& order, const std::string& sampleName,
                                    double avgProductionTime, double yieldRate) {
    const Sample* sample = m_sampleCtrl.findById(order.getSampleId());
    int currentStock = sample ? sample->getStock() : 0;
    int shortage = order.getQuantity() - currentStock;
    if (shortage < 0) shortage = 0;

    int actualProduction = ProductionLine::calcActualProduction(shortage, yieldRate);
    double totalMinutes = ProductionLine::calcTotalProductionMinutes(avgProductionTime, actualProduction);

    ProductionItem item;
    item.orderId = order.getOrderId();
    item.sampleId = order.getSampleId();
    item.sampleName = sampleName;
    item.orderQuantity = order.getQuantity();
    item.shortage = shortage;
    item.actualProduction = actualProduction;
    item.totalProductionMinutes = totalMinutes;

    m_line.enqueue(item);
}

const ProductionItem* ProductionController::getCurrentItem() const {
    return m_line.getCurrentItem();
}

std::queue<ProductionItem> ProductionController::getWaitingQueue() const {
    return m_line.getWaitingQueue();
}

int ProductionController::getWaitingCount() const {
    return static_cast<int>(m_line.getWaitingQueue().size());
}

void ProductionController::completeCurrentItem(
    std::function<void(const std::string& orderId)> onComplete)
{
    const ProductionItem* item = m_line.getCurrentItem();
    if (!item) return;

    m_sampleCtrl.addStock(item->sampleId, item->actualProduction);
    std::string orderId = item->orderId;
    m_line.completeCurrentItem();
    onComplete(orderId);
}

bool ProductionController::isEmpty() const {
    return m_line.isEmpty();
}
