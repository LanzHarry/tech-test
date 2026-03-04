#ifndef STREAMINGTRADELOADER_H
#define STREAMINGTRADELOADER_H

#include "../Loaders/ITradeLoader.h"
#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include <map>
#include <string>
#include <vector>

class StreamingTradeLoader {
  private:
    std::map<std::string, std::unique_ptr<IPricingEngine>> enginesByTypeName_;
    std::map<std::string, IPricingEngine *> pricers_;

    std::vector<ITradeLoader *> getTradeLoaders();
    void loadPricers();

  public:
    ~StreamingTradeLoader() = default;

    void loadAndPrice(IScalarResultReceiver *resultReceiver);
};

#endif // STREAMINGTRADELOADER_H
