#ifndef BASEPRICER_H
#define BASEPRICER_H

#include "IPricer.h"
#include <map>
#include <string>

class BasePricer : public IPricer {
  private:
    std::map<std::string, std::unique_ptr<IPricingEngine>> enginesByTypeName_;

  protected:
    std::map<std::string, IPricingEngine *> pricers_;
    void loadPricers();

  public:
    BasePricer();
    const std::map<std::string, IPricingEngine *> &getPricers() override {
        return pricers_;
    }
};

#endif // BASEPRICER_H
