#include "FxTradeLoader.h"
#include <stdexcept>

ITrade *FxTradeLoader::createTradeFromLine(const std::string &line) const {
    std::vector<std::string> items = utils::delimSplit(line, separator);
    std::stringstream ss(line);
    std::string item;

std::vector<ITrade *> FxTradeLoader::loadTrades() const {
    throw std::runtime_error("Not implemented");
}

    return trade;
}

int FxTradeLoader::linesToSkip() const {
    return 2;
}
