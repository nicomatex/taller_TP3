#ifndef __PLAYER_HANDLER_H
#define __PLAYER_HANDLER_H

#include "common_socket.h"
#include "server_thread.h"
#include <atomic>
#include <mutex>

class PlayerHandler:public Thread{
    private:
        std::mutex m;
        Socket peer;
        std::atomic_bool is_dead;
    public:
        PlayerHandler(Socket peer);
        
        /* Cierra la conexion para este jugador.*/
        void stop();

        /* Metodo que contiene la logica del handling. */
        virtual void run() override;
};

#endif