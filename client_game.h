#ifndef __GAME_H
#define __GAME_H

#include <string>
#include "client_generic.h"
#include "client_command.h"
#include "client_parser.h"

class Game{
    private:
        Client client;
        ClientParser parser;
        
    public:
        /* Recibe una respuesta del servidor. */
        std::string receive_response();

        /* Envia un comando al servidor. */
        void send_command(Command* command);

        /* Inicia el parseo de comandos y comunicacion 
        con el servidor.*/
        void run();

        /* Recibe el host y puerto del servidor e intenta
        conectarse.*/
        Game(const char* host,const char* port);
        ~Game();
};

#endif