#ifndef BONDTRADELOADER_H
#define BONDTRADELOADER_H

#include "BaseTradeLoader.h"
#include <string>

class BondTradeLoader : public BaseTradeLoader {
  private:
    static constexpr char separator = ',';

  protected:
    ITrade *createTradeFromLine(const std::string &line) const override;
};

#endif // BONDTRADELOADER_H
