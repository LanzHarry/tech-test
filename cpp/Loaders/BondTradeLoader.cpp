#include "BondTradeLoader.h"
#include "Models/BondTrade.h"
#include "Utils/utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

ITrade *BondTradeLoader::createTradeFromLine(const std::string &line) const {
    std::vector<std::string> items;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, separator)) {
        items.push_back(utils::trim(item));
    }

    if (items.size() < 7) {
        throw std::runtime_error("Invalid line format");
    }

    // BondTrade takes a trade id and a trade type
    // items[6] is trade id and items[0] is trade type
    // TODO: replace magic numbers with enum
    BondTrade *trade = new BondTrade(items[6], items[0]);

    std::tm tm = {};
    std::istringstream dateStream(items[1]);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade->setTradeDate(timePoint);

    trade->setInstrument(items[2]);
    trade->setCounterparty(items[3]);
    trade->setNotional(std::stod(items[4]));
    trade->setRate(std::stod(items[5]));

    return trade;
}
