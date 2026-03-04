#ifndef BASETRADELOADER_H
#define BASETRADELOADER_H

#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "ITradeLoader.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

class BaseTradeLoader : public ITradeLoader {
  private:
    void loadTradesFromFile(const std::string &filename, std::vector<ITrade *> &out) const;

  protected:
    std::string dataFile_;

    virtual ITrade *createTradeFromLine(const std::string &line) const = 0;
    virtual int linesToSkip() const {
        return 1;
    }

  public:
    void streamTrades(std::function<void(ITrade *)> onTrade) const override;
    std::vector<ITrade *> loadTrades() const override;
    std::string getDataFile() const override;
    void setDataFile(const std::string &file) override;
};

#endif // BASETRADELOADER_H
