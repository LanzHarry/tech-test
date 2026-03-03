#include "PricingConfigLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string PricingConfigLoader::getConfigFile() const {
    return configFile_;
}

void PricingConfigLoader::setConfigFile(const std::string &file) {
    configFile_ = file;
}

static std::string extractAttribute(const std::string &tag, const std::string &attr) {
    std::string search = attr + "=\"";
    size_t start = tag.find(search);
    if (start == std::string::npos)
        throw std::runtime_error("Attribute not found: " + attr);
    start += search.length();
    size_t end = tag.find('"', start);
    if (end == std::string::npos)
        throw std::runtime_error("Malformed attribute: " + attr);
    return tag.substr(start, end - start);
}

PricingEngineConfig PricingConfigLoader::parseXml(const std::string &content) {
    PricingEngineConfig config;
    size_t pos = 0;
    while ((pos = content.find("<Engine", pos)) != std::string::npos) {
        size_t end = content.find("/>", pos);
        if (end == std::string::npos)
            throw std::runtime_error("Malformed engine element");
        std::string tag = content.substr(pos, end - pos);
        PricingEngineConfigItem item;
        item.setTradeType(extractAttribute(tag, "tradeType"));
        item.setAssembly(extractAttribute(tag, "assembly"));
        item.setTypeName(extractAttribute(tag, "pricingEngine"));
        config.push_back(item);
        pos = end;
    }
    return config;
}

PricingEngineConfig PricingConfigLoader::loadConfig() {
    if (configFile_.empty())
        throw std::invalid_argument("Config file path not set");

    std::ifstream stream(configFile_);
    if (!stream.is_open())
        throw std::runtime_error("Cannot open file: " + configFile_);

    std::ostringstream buffer;
    buffer << stream.rdbuf();
    return parseXml(buffer.str());
}
