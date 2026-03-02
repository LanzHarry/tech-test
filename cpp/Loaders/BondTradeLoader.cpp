#include "BondTradeLoader.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

BondTrade *BondTradeLoader::createTradeFromLine(const std::string &line) {
    std::vector<std::string> items;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, separator)) {
        items.push_back(item);
    }

    if (items.size() < 7) {
        throw std::runtime_error("Invalid line format");
    }

    BondTrade *trade = new BondTrade(items[6]);

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

void BondTradeLoader::loadTradesFromFile(const std::string &filename,
                                         std::vector<ITrade *> &out) const {
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }

    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    std::getline(stream, line); // skip first line
    while (std::getline(stream, line)) {
        out.push_back(createTradeFromLine(line));
    }
}

std::vector<ITrade *> BondTradeLoader::loadTrades() const {
    std::vector<ITrade *> result;
    loadTradesFromFile(dataFile_, result);
    return result;
}

std::string BondTradeLoader::getDataFile() const {
    return dataFile_;
}

void BondTradeLoader::setDataFile(const std::string &file) {
    dataFile_ = file;
}
