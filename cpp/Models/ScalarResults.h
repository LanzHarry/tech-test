#ifndef SCALARRESULTS_H
#define SCALARRESULTS_H

#include "IScalarResultReceiver.h"
#include "ScalarResult.h"
#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <vector>

class ScalarResults : public IScalarResultReceiver {
  public:
    ~ScalarResults();
    std::optional<ScalarResult> operator[](const std::string &tradeId) const;

    bool containsTrade(const std::string &tradeId) const;

    void addResult(const std::string &tradeId, double result) override;

    void addError(const std::string &tradeId, const std::string &error) override;

    class Iterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ScalarResult;
        using difference_type = std::ptrdiff_t;
        using pointer = ScalarResult *;
        using reference = ScalarResult &;

        Iterator(std::vector<ScalarResult>::const_iterator it) : it_(it) {};

        // Iterator must be constructable from ScalarResults parent
        Iterator &operator++();
        ScalarResult operator*() const;
        bool operator!=(const Iterator &other) const;

      private:
        std::vector<ScalarResult>::const_iterator it_;
    };

    Iterator begin() const;
    Iterator end() const;

  private:
    std::map<std::string, double> results_;
    std::map<std::string, std::string> errors_;
    mutable bool cacheInvalid_ = true;
    mutable std::vector<ScalarResult> scalarResults_;

    void rebuildCacheIfInvalid() const;
};

#endif // SCALARRESULTS_H
