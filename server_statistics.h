#ifndef __STATISTICS_H
#define __STATISTICS_H

/* ------ Includes ---------*/
#include <mutex>

/* ------ Interfaz ---------*/
class Statistics {
   private:
    std::mutex m;
    unsigned int winners;
    unsigned int losers;

   public:
    Statistics();
    ~Statistics();

    /* Agrega un ganador a las estadisticas */
    void add_winner();

    /* Agrega un perdedor a las estadisticas */
    void add_loser();

    void print_stats();
};

#endif

