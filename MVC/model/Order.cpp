#include "Order.h"

Order::Order(std::string orderId, std::string sampleId,
             std::string customerName, int quantity, std::string createdAt)
    : m_orderId(std::move(orderId))
    , m_sampleId(std::move(sampleId))
    , m_customerName(std::move(customerName))
    , m_quantity(quantity)
    , m_createdAt(std::move(createdAt))
{}

std::string Order::statusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::RESERVED:  return "RESERVED";
        case OrderStatus::CONFIRMED: return "CONFIRMED";
        case OrderStatus::PRODUCING: return "PRODUCING";
        case OrderStatus::RELEASE:   return "RELEASE";
        case OrderStatus::REJECTED:  return "REJECTED";
    }
    return "UNKNOWN";
}
