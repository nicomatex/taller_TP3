#include <arpa/inet.h>
#include <cstring>
#include <utility>
#include <vector>

#include "client_game.h"
#include "client_config.h"
#include "common_network_error.h"
#include "common_config.h"

Game::Game(const char* host, const char* port)
    : protocol(Socket(host,port)){}

void Game::send_command(Command* command) {
    protocol.send_command(command);
    delete command;
}

void Game::run() {
    bool continue_running = true;
    std::string response;
    while (continue_running) {
        try {
            send_command(parser());
            response = std::move(protocol.receive_string());

            /* Comprobacion de fin de partida */
            if (response == RESP_LOSE || response == RESP_WIN) {
                continue_running = false;
            }

            /* Comprobacion de desconexion */
            if (response.length() == 0) {
                std::cerr << MSG_ERR_CLOSED << std::endl;
                continue_running = false;
            } else {
                std::cout << response << std::endl;
            }
        } catch (NetworkError& e) {
            std::cerr << e.what() << std::endl;
            continue_running = false;
        } catch (...) {
            std::cerr << MSG_ERR_UNKNOWN << std::endl;
            continue_running = false;
        }
    }
}

Game::~Game() {}
