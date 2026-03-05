#include "ScreenResultPrinter.h"
#include <iostream>

void ScreenResultPrinter::printResults(const ScalarResults &results) {
    constexpr const char *sepString = " : ";
    for (const auto &result : results) {
        // Write code here to print out the results such that we have:
        // TradeID : Result : Error
        // If there is no result then the output should be:
        // TradeID : Error
        // If there is no error the output should be:
        // TradeID : Result
        std::string resultString = result.getTradeId();
        if (result.getResult().has_value()) {
            resultString += sepString + std::to_string(result.getResult().value());
        }
        if (result.getError().has_value()) {
            resultString += sepString + result.getError().value();
        }
        std::cout << resultString << "\n";
    }
}
