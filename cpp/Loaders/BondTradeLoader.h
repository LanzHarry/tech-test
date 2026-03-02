#ifndef BONDTRADELOADER_H
#define BONDTRADELOADER_H

#include "../Models/BondTrade.h"
// #include "../Models/BondTradeList.h" // using BondTradeList removed to avoid use after free
#include "ITradeLoader.h"
// #include <memory>
#include <string>
#include <vector>

class BondTradeLoader : public ITradeLoader {
  private:
    static constexpr char separator = ',';
    std::string dataFile_;

    BondTrade *createTradeFromLine(const std::string &line) const;
    void loadTradesFromFile(const std::string &filename, std::vector<ITrade *> &out) const;

  public:
    std::vector<ITrade *> loadTrades() const override;
    std::string getDataFile() const override;
    void setDataFile(const std::string &file) override;
};

#endif // BONDTRADELOADER_H
