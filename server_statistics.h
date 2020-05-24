#ifndef __STATISTICS_H
#define __STATISTICS_H

#include <mutex>

class Statistics{
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
        
        unsigned int get_winners();
        unsigned int get_losers();
};

#endif
