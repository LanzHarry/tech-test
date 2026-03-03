#include "BaseTradeLoader.h"
#include <fstream>
#include <stdexcept>

void BaseTradeLoader::loadTradesFromFile(const std::string &filename,
                                         std::vector<ITrade *> &out) const {
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }

    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    for (int i = 0; i < linesToSkip(); ++i)
        std::getline(stream, line);

    while (std::getline(stream, line)) {
        // omit lines that start with end as in fxtrade dat file, could use startswith in c++20
        if (line.empty() || line.rfind("END", 0) == 0)
            continue;
        out.push_back(createTradeFromLine(line));
    }
}

std::vector<ITrade *> BaseTradeLoader::loadTrades() const {
    std::vector<ITrade *> result;
    loadTradesFromFile(dataFile_, result);
    return result;
}

std::string BaseTradeLoader::getDataFile() const {
    return dataFile_;
}

void BaseTradeLoader::setDataFile(const std::string &file) {
    dataFile_ = file;
}
