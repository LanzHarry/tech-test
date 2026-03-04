#include "StreamingTradeLoader.h"
#include "../Loaders/BondTradeLoader.h"
#include "../Loaders/FxTradeLoader.h"
#include "../Pricers/CorpBondPricingEngine.h"
#include "../Pricers/FxPricingEngine.h"
#include "../Pricers/GovBondPricingEngine.h"
#include "PricingConfigLoader.h"
#include <stdexcept>

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

void StreamingTradeLoader::loadPricers() {
    PricingConfigLoader pricingConfigLoader;
    pricingConfigLoader.setConfigFile("./PricingConfig/PricingEngines.xml");
    PricingEngineConfig pricerConfig = pricingConfigLoader.loadConfig();

    for (const auto &configItem : pricerConfig) {
        const std::string &typeName = configItem.getTypeName();

        // check if engine not already seen
        if (enginesByTypeName_.find(typeName) == enginesByTypeName_.end()) {
            std::unique_ptr<IPricingEngine> engine;
            if (typeName == "HmxLabs.TechTest.Pricers.GovBondPricingEngine") {
                engine = std::make_unique<GovBondPricingEngine>();
            } else if (typeName == "HmxLabs.TechTest.Pricers.CorpBondPricingEngine") {
                engine = std::make_unique<CorpBondPricingEngine>();
            } else if (typeName == "HmxLabs.TechTest.Pricers.FxPricingEngine") {
                engine = std::make_unique<FxPricingEngine>();
            } else {
                throw std::runtime_error("Unknown pricing engine type: " + typeName);
            }
            pricers_[configItem.getTradeType()] = engine.get();
            enginesByTypeName_[typeName] = std::move(engine);
        } else {
            pricers_[configItem.getTradeType()] = enginesByTypeName_[typeName].get();
        }
    }
}

void StreamingTradeLoader::loadAndPrice(IScalarResultReceiver *resultReceiver) {
    // load pricers, get trade loaders, stream the trades, delete the loaders
    loadPricers();
    auto loaders = getTradeLoaders();
    for (auto *loader : loaders) {
        loader->streamTrades(pricers_, resultReceiver);
        delete loader;
    }
}
