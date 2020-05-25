#ifndef __GAME_H
#define __GAME_H

/* ------ Includes ---------*/
#include <string>
#include "common_command.h"
#include "client_parser.h"
#include "common_protocol.h"

/* ------ Interfaz ---------*/
class Game {
   private:
    ClientParser parser;
    Protocol protocol;

   public:
    /* Envia un comando al servidor. */
    void send_command(Command* command);

    /* Inicia el parseo de comandos y comunicacion
    con el servidor.*/
    void run();

    /* Recibe el host y puerto del servidor e intenta
    conectarse.*/
    Game(const char* host, const char* port);
    ~Game();
};

#endif
