#ifndef BASETRADELOADER_H
#define BASETRADELOADER_H

#include "ITradeLoader.h"
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
    std::vector<ITrade *> loadTrades() const override;
    std::string getDataFile() const override;
    void setDataFile(const std::string &file) override;
};

#endif // BASETRADELOADER_H
