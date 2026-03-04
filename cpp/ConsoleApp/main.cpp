#include "../Models/ScalarResults.h"
#include "../RiskSystem/ParallelPricer.h"
#include "../RiskSystem/ScreenResultPrinter.h"
#include "../RiskSystem/SerialPricer.h"
#include "../RiskSystem/SerialTradeLoader.h"
#include "../RiskSystem/StreamingTradeLoader.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int main(int argc, char *argv[]) {
    // SerialTradeLoader tradeLoader;
    // auto allTrades = tradeLoader.loadTrades();
    //
    // ScalarResults results;
    // SerialPricer pricer;
    // pricer.price(allTrades, &results);
    //
    // for (auto &tradeVec : allTrades) {
    //     for (auto *tradeElt : tradeVec) {
    //         delete tradeElt;
    //     }
    // }

    ScalarResults results;
    SerialPricer serialPricer;
    StreamingTradeLoader streamingTradeLoader;
    streamingTradeLoader.loadAndPrice(serialPricer.getPricers(), &results);

    ScreenResultPrinter::printResults(results);

    std::cout << "Press any key to exit.." << "\n";
    _getch();

    return 0;
}
