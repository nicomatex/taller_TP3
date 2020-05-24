
#include <arpa/inet.h>
#include <cstring>
#include <utility>
#include <vector>

#include "client_game.h"
#include "client_config.h"
#include "common_network_error.h"
#include "common_config.h"

Game::Game(const char* host, const char* port)
    : client(host, port), protocol(client.get_socket()) {}

void Game::send_command(Command* command) {
    client.send_message(command->get_serialization());
    delete command;
}

std::string Game::receive_response() {
    std::vector<uint8_t> res_size_buffer =
        std::move(client.recieve_message(sizeof(uint16_t)));

    uint16_t res_size = 0;
    memcpy(&res_size, &res_size_buffer[0], sizeof(uint16_t));

    res_size = ntohs(res_size);

    std::vector<uint8_t> res_buffer =
        std::move(client.recieve_message((size_t)res_size));
    std::string response;

    for (size_t i = 0; i < res_buffer.size(); i++) {
        response.push_back((char)res_buffer[i]);
    }

    return response;
}

void Game::run() {
    bool continue_running = true;
    std::string response;
    while (continue_running) {
        try {
            send_command(parser());
            response = std::move(receive_response());
            if (response == RESP_LOSE || response == RESP_WIN) {
                continue_running = false;
            }
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
