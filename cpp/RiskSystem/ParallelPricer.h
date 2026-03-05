#ifndef PARALLELPRICER_H
#define PARALLELPRICER_H

#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include "BasePricer.h"
#include "PricingConfigLoader.h"
#include <future>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class ParallelPricer : public BasePricer {
  private:
    std::mutex resultMutex_;

  public:
    ~ParallelPricer() = default;
    void price(const std::vector<std::vector<ITrade *>> &tradeContainers,
               IScalarResultReceiver *resultReceiver) override;
};

#endif // PARALLELPRICER_H
