#ifndef FXTRADELOADER_H
#define FXTRADELOADER_H

#include "../Models/FxTrade.h"
#include "BaseTradeLoader.h"
#include <string>
#include <vector>

class FxTradeLoader : public BaseTradeLoader {
  private:
    static constexpr const char *separator = "\xC2\xAC"; // UTF-8 encoding of ¬

  protected:
    ITrade *createTradeFromLine(const std::string &line) const override;
    int linesToSkip() const override;
};

#endif // FXTRADELOADER_H
