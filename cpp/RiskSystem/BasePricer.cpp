#include "BasePricer.h"
#include "../Models/IPricingEngine.h"
#include "../Pricers/CorpBondPricingEngine.h"
#include "../Pricers/FxPricingEngine.h"
#include "../Pricers/GovBondPricingEngine.h"
#include "PricingConfigLoader.h"
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

BasePricer::BasePricer() {
    loadPricers();
}

void BasePricer::loadPricers() {
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
