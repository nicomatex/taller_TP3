#include <iostream>

#include "server_statistics.h"
#include "server_config.h"

Statistics::Statistics() : winners(0), losers(0) {}

Statistics::~Statistics() {}

void Statistics::add_loser() {
    std::unique_lock<std::mutex> l(m);
    losers += 1;
}

void Statistics::add_winner() {
    std::unique_lock<std::mutex> l(m);
    winners += 1;
}

void Statistics::print_stats() {
    std::unique_lock<std::mutex> l(m);
    std::cout << MSG_STATS << ":\n\t";
    std::cout << MSG_WINNERS << ":  " << winners;
    std::cout << "\n\t";
    std::cout << MSG_LOSERS << ": " << losers << "\n";
}
