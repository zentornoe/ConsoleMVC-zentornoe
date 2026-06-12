#pragma once
#include <string>

enum class OrderStatus {
    RESERVED,
    CONFIRMED,
    PRODUCING,
    RELEASE,
    REJECTED
};

class Order {
public:
    Order() = default;
    Order(std::string orderId, std::string sampleId,
          std::string customerName, int quantity, std::string createdAt);

    const std::string& getOrderId() const { return m_orderId; }
    const std::string& getSampleId() const { return m_sampleId; }
    const std::string& getCustomerName() const { return m_customerName; }
    int getQuantity() const { return m_quantity; }
    OrderStatus getStatus() const { return m_status; }
    const std::string& getCreatedAt() const { return m_createdAt; }
    const std::string& getUpdatedAt() const { return m_updatedAt; }
    const std::string& getReleasedAt() const { return m_releasedAt; }

    void setStatus(OrderStatus status) { m_status = status; }
    void setUpdatedAt(const std::string& dt) { m_updatedAt = dt; }
    void setReleasedAt(const std::string& dt) { m_releasedAt = dt; }

    static std::string statusToString(OrderStatus status);

private:
    std::string m_orderId;
    std::string m_sampleId;
    std::string m_customerName;
    int m_quantity{ 0 };
    OrderStatus m_status{ OrderStatus::RESERVED };
    std::string m_createdAt;
    std::string m_updatedAt;
    std::string m_releasedAt;
};
