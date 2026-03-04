#include "StreamingTradeLoader.h"
#include "../Loaders/BondTradeLoader.h"
#include "../Loaders/FxTradeLoader.h"

std::vector<ITradeLoader *> StreamingTradeLoader::getTradeLoaders() {
    std::vector<ITradeLoader *> loaders;

    BondTradeLoader *bondLoader = new BondTradeLoader();
    bondLoader->setDataFile("TradeData/BondTrades.dat");
    loaders.push_back(bondLoader);

    FxTradeLoader *fxLoader = new FxTradeLoader();
    fxLoader->setDataFile("TradeData/FxTrades.dat");
    loaders.push_back(fxLoader);

    return loaders;
}

void StreamingTradeLoader::loadAndPrice(const std::map<std::string, IPricingEngine *> &pricers,
                                        IScalarResultReceiver *resultReceiver) {
    auto loaders = getTradeLoaders();

    for (auto *loader : loaders) {
        loader->streamTrades([&pricers, resultReceiver](ITrade *trade) {
            auto it = pricers.find(trade->getTradeType());
            if (it != pricers.end()) {
                it->second->price(trade, resultReceiver);
            } else {
                resultReceiver->addError(trade->getTradeId(),
                                         "No pricing engine available for trade type: " +
                                             trade->getTradeType());
            }
        });
        delete loader;
    }
}
