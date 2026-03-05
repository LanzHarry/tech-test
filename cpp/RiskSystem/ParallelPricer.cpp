#include "ParallelPricer.h"

class ThreadSafeResultReceiver : public IScalarResultReceiver {
  public:
    ThreadSafeResultReceiver(IScalarResultReceiver *inner, std::mutex &mutex)
        : inner_(inner), mutex_(mutex) {}

    void addResult(const std::string &tradeId, double result) override {
        std::lock_guard<std::mutex> lock(mutex_);
        inner_->addResult(tradeId, result);
    }

    void addError(const std::string &tradeId, const std::string &error) override {
        std::lock_guard<std::mutex> lock(mutex_);
        inner_->addError(tradeId, error);
    }

  private:
    IScalarResultReceiver *inner_;
    std::mutex &mutex_;
};

void ParallelPricer::price(const std::vector<std::vector<ITrade *>> &tradeContainers,
                           IScalarResultReceiver *resultReceiver) {
    ThreadSafeResultReceiver safeReceiver(resultReceiver, resultMutex_);
    std::vector<std::future<void>> futures;

    for (const auto &tradeContainer : tradeContainers) {
        for (ITrade *trade : tradeContainer) {
            const std::string &tradeType = trade->getTradeType();
            auto it = pricers_.find(tradeType);

            if (it == pricers_.end()) {
                safeReceiver.addError(trade->getTradeId(),
                                      "No pricing engine available for trade type: " + tradeType);
                continue;
            }

            IPricingEngine *pricer = it->second;

            // launch async task and store future
            // a more production grade approach might be N std::thread::hardware_concurrency workers
            // from a thread pool depending on hardware and number of trades to price
            futures.push_back(std::async(std::launch::async, [pricer, trade, &safeReceiver]() {
                pricer->price(trade, &safeReceiver);
            }));
        }
    }

    for (auto &future : futures) {
        future.get();
    }
}
