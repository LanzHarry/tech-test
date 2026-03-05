#ifndef IPRICER_H
#define IPRICER_H

#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include <map>
#include <string>
#include <vector>

class IPricer {
  public:
    virtual ~IPricer() = default;
    virtual void price(const std::vector<std::vector<ITrade *>> &tradeContainers,
                       IScalarResultReceiver *resultReceiver) = 0;
    virtual const std::map<std::string, IPricingEngine *> &getPricers() const = 0;
};

#endif // IPRICER_H
