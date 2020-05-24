#include "server_statistics.h"

Statistics::Statistics():winners(0),losers(0){}

Statistics::~Statistics(){}

void Statistics::add_loser(){
    std::unique_lock<std::mutex> l(m);
    losers += 1;
}

void Statistics::add_winner(){
    std::unique_lock<std::mutex> l(m);
    winners += 1;
}

unsigned int Statistics::get_losers(){
    std::unique_lock<std::mutex> l(m);
    return losers;
}

unsigned int Statistics::get_winners(){
    std::unique_lock<std::mutex> l(m);
    return winners;
}