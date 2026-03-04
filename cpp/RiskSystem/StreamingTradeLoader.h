#ifndef STREAMINGTRADELOADER_H
#define STREAMINGTRADELOADER_H

#include "../Loaders/ITradeLoader.h"
#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include <map>
#include <string>
#include <vector>

class StreamingTradeLoader {
  private:
    std::vector<ITradeLoader *> getTradeLoaders();

  public:
    ~StreamingTradeLoader() = default;

    void loadAndPrice(const std::map<std::string, IPricingEngine *> &pricers,
                      IScalarResultReceiver *resultReceiver);
};

#endif // STREAMINGTRADELOADER_H
