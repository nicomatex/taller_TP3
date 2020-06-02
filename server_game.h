#ifndef __GAME_SERVER_H
#define __GAME_SERVER_H

/* ------ Includes ---------*/
#include <atomic>
#include <cstdint>
#include <mutex>
#include <vector>
#include "common_number_parser.h"
#include "server_player_handler.h"
#include "server_statistics.h"

/* ------ Interfaz ---------*/
class GameServer {
   private:
    Socket acceptor;
    std::atomic_bool accepting_connections;
    NumberParser parser;
    const char* number_file_name;
    Statistics stats;
    std::vector<PlayerHandler*> players;

    /* Carrusel de numeros utilizados para que los clientes adivinen*/
    std::vector<uint16_t> numbers;

    /* Indice utilizado para el carrusel de numeros. */
    size_t i_number;

    /* Utilizada por la clase en el hilo aceptador. */
    void _accept_connections();

    /* Agrega un jugador al vector players. Es thread-safe */
    void _add_peer(PlayerHandler* player);

    /* Quita los clientes desconectados/muertos de la lista. Es thread-safe */
    void _remove_dead();

   public:
    /* Recibe en su constructor el puerto y la ruta
    al archivo con numeros.*/
    GameServer(const char* port, const char* numbers_file);
    ~GameServer();

    /* Inicia la ejecucion del servidor. */
    void run();
};

#endif
