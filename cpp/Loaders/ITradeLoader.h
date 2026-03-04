#ifndef ITRADELOADER_H
#define ITRADELOADER_H

#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

class ITradeLoader {
  public:
    virtual ~ITradeLoader() = default;
    virtual void streamTrades(std::function<void(ITrade *)> onTrade) const = 0;
    virtual std::vector<ITrade *> loadTrades() const = 0;
    virtual std::string getDataFile() const = 0;
    virtual void setDataFile(const std::string &file) = 0;
};

#endif // ITRADELOADER_H
