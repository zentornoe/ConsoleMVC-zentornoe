#pragma once
#include "../model/Sample.h"
#include <vector>
#include <string>
#include <optional>

class SampleController {
public:
    // 시료 등록. ID 중복 시 false 반환
    bool addSample(const std::string& name, double avgProductionTime,
                   double yieldRate, int initialStock);

    // 전체 시료 목록 반환
    const std::vector<Sample>& getAllSamples() const;

    // ID로 시료 조회
    Sample* findById(const std::string& id);
    const Sample* findById(const std::string& id) const;

    // 이름(부분 일치)으로 시료 검색
    std::vector<const Sample*> searchByName(const std::string& keyword) const;

    // 재고 차감 (성공 시 true)
    bool reduceStock(const std::string& sampleId, int amount);

    // 재고 추가
    void addStock(const std::string& sampleId, int amount);

    // 다음 시료 ID 생성 (S-001, S-002, ...)
    std::string generateNextId() const;

private:
    std::vector<Sample> m_samples;
};
