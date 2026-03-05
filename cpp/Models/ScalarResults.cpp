#include "ScalarResults.h"
#include <set>
#include <stdexcept>

ScalarResults::~ScalarResults() = default;

std::optional<ScalarResult> ScalarResults::operator[](const std::string &tradeId) const {
    if (!containsTrade(tradeId)) {
        return std::nullopt;
    }

    std::optional<double> priceResult = std::nullopt;
    std::optional<std::string> error = std::nullopt;

    auto resultIt = results_.find(tradeId);
    if (resultIt != results_.end()) {
        priceResult = resultIt->second;
    }

    auto errorIt = errors_.find(tradeId);
    if (errorIt != errors_.end()) {
        error = errorIt->second;
    }

    return ScalarResult(tradeId, priceResult, error);
}

bool ScalarResults::containsTrade(const std::string &tradeId) const {
    return results_.find(tradeId) != results_.end() || errors_.find(tradeId) != errors_.end();
}

void ScalarResults::addResult(const std::string &tradeId, double result) {
    results_[tradeId] = result;
    cacheInvalid_ = true;
}

void ScalarResults::addError(const std::string &tradeId, const std::string &error) {
    errors_[tradeId] = error;
    cacheInvalid_ = true;
}

ScalarResults::Iterator &ScalarResults::Iterator::operator++() {
    ++it_;
    return *this;
}

ScalarResult ScalarResults::Iterator::operator*() const {
    return *it_;
}

bool ScalarResults::Iterator::operator!=(const Iterator &other) const {
    return it_ != other.it_;
}

ScalarResults::Iterator ScalarResults::begin() const {
    rebuildCacheIfInvalid();
    return Iterator(scalarResults_.begin());
}

ScalarResults::Iterator ScalarResults::end() const {
    rebuildCacheIfInvalid();
    return Iterator(scalarResults_.end());
}

void ScalarResults::rebuildCacheIfInvalid() const {
    if (!cacheInvalid_)
        return;
    scalarResults_.clear();
    std::set<std::string> tradeIds;
    for (const auto &[id, _] : results_)
        tradeIds.insert(id);
    for (const auto &[id, _] : errors_)
        tradeIds.insert(id);
    for (const auto &tradeId : tradeIds) {
        scalarResults_.push_back((*this)[tradeId].value());
    }
    cacheInvalid_ = false;
}
