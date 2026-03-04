#ifndef SERIALPRICER_H
#define SERIALPRICER_H

#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include "BasePricer.h"
#include <vector>

class SerialPricer : public BasePricer {
  public:
    ~SerialPricer() = default;

    void price(const std::vector<std::vector<ITrade *>> &tradeContainers,
               IScalarResultReceiver *resultReceiver) override;
};

#endif // SERIALPRICER_H
