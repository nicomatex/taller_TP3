#ifndef __PLAYER_HANDLER_H
#define __PLAYER_HANDLER_H

/* ------ Includes ---------*/
#include <atomic>
#include <mutex>
#include <string>
#include "common_socket.h"
#include "common_number_parser.h"
#include "server_statistics.h"
#include "server_thread.h"
#include "common_protocol.h"

/* ------ Interfaz ---------*/
class PlayerHandler : public Thread {
   private:
    std::mutex m;
    Statistics* stats;
    NumberParser* parser;
    Protocol protocol;

    std::atomic_bool is_dead;
    /* Numero que debe adivinar el cliente. */
    const uint16_t guess_number;

    size_t tries_left;
    bool player_won;

    /* Handlers para los comandos. */
    void _handle_help();
    void _handle_surrender();
    void _handle_number();

    /* Genera la string de respuesta a un numero, indicando
    la cantidad de regular, bien, o mal.*/
    std::string _get_hints(uint16_t number);

   public:
    PlayerHandler(Socket peer, Statistics* stats, NumberParser* parser,
                  const uint16_t guess_number);

    /* Cierra la conexion para este jugador.*/
    void stop();

    /* Metodo que contiene la logica del handling. */
    virtual void run() override;

    bool dead();
};

#endif
