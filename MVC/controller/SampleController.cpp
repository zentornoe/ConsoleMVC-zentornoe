#include "SampleController.h"
#include <algorithm>
#include <format>

bool SampleController::addSample(const std::string& name, double avgProductionTime,
                                  double yieldRate, int initialStock) {
    std::string newId = generateNextId();
    m_samples.emplace_back(newId, name, avgProductionTime, yieldRate, initialStock);
    return true;
}

const std::vector<Sample>& SampleController::getAllSamples() const {
    return m_samples;
}

Sample* SampleController::findById(const std::string& id) {
    for (auto& s : m_samples) {
        if (s.getId() == id) return &s;
    }
    return nullptr;
}

const Sample* SampleController::findById(const std::string& id) const {
    for (const auto& s : m_samples) {
        if (s.getId() == id) return &s;
    }
    return nullptr;
}

std::vector<const Sample*> SampleController::searchByName(const std::string& keyword) const {
    std::vector<const Sample*> results;
    for (const auto& s : m_samples) {
        if (s.getName().find(keyword) != std::string::npos) {
            results.push_back(&s);
        }
    }
    return results;
}

bool SampleController::reduceStock(const std::string& sampleId, int amount) {
    Sample* s = findById(sampleId);
    if (!s) return false;
    return s->reduceStock(amount);
}

void SampleController::addStock(const std::string& sampleId, int amount) {
    Sample* s = findById(sampleId);
    if (s) s->addStock(amount);
}

std::string SampleController::generateNextId() const {
    int next = static_cast<int>(m_samples.size()) + 1;
    return std::format("S-{:03d}", next);
}
