#include "SerialPricer.h"
#include "../Pricers/CorpBondPricingEngine.h"
#include "../Pricers/FxPricingEngine.h"
#include "../Pricers/GovBondPricingEngine.h"
#include <memory>
#include <stdexcept>

void SerialPricer::loadPricers() {
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

void SerialPricer::price(const std::vector<std::vector<ITrade *>> &tradeContainers,
                         IScalarResultReceiver *resultReceiver) {
    loadPricers();

    for (const auto &tradeContainer : tradeContainers) {
        for (ITrade *trade : tradeContainer) {
            std::string tradeType = trade->getTradeType();
            if (pricers_.find(tradeType) == pricers_.end()) {
                resultReceiver->addError(trade->getTradeId(),
                                         "No Pricing Engines available for this trade type");
                continue;
            }

            IPricingEngine *pricer = pricers_[tradeType];
            pricer->price(trade, resultReceiver);
        }
    }
}
