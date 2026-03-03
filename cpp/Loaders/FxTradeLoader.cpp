#include "FxTradeLoader.h"
#include "Models/FxTrade.h"
#include "Utils/utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

ITrade *FxTradeLoader::createTradeFromLine(const std::string &line) const {
    std::vector<std::string> items = utils::delimSplit(line, separator);
    std::stringstream ss(line);
    std::string item;

    if (items.size() < 9) {
        throw std::runtime_error("Invalid line format");
    }

    // FxTrade takes a trade id and a trade type
    // items[8] is trade id and items[0] is trade type
    // TODO: replace magic numbers with enum
    FxTrade *trade = new FxTrade(items[8], items[0]);

    trade->setTradeDate(utils::parseDate(items[1], "%Y-%m-%d"));
    trade->setInstrument(items[2] + items[3]);
    trade->setNotional(std::stod(items[4]));
    trade->setRate(std::stod(items[5]));
    trade->setValueDate(utils::parseDate(items[6], "%Y-%m-%d"));
    trade->setCounterparty(items[7]);

    return trade;
}

int FxTradeLoader::linesToSkip() const {
    return 2;
}
