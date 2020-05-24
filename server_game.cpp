#include <iostream>
#include <string>
#include <thread>
#include <utility>

#include "server_game.h"
#include "common_network_error.h"
#include "server_config.h"

GameServer::GameServer(const char* port, const char* numbers_file)
    : server(port),
      accepting_connections(true),
      parser(numbers_file),
      i_number(0) {}

GameServer::~GameServer() {}

void GameServer::_add_peer(PlayerHandler* player) { players.push_back(player); }

void GameServer::_remove_dead() {
    std::vector<PlayerHandler*>::iterator it = players.begin();

    while (it != players.end()) {
        if ((*it)->dead()) {
            (*it)->join();
            delete (*it);
            it = players.erase(it);
        } else {
            ++it;
        }
    }
}

void GameServer::_accept_connections() {
    while (accepting_connections) {
        try {
            Socket peer = std::move(server.accept_connection());
            PlayerHandler* player = new PlayerHandler(
                std::move(peer), &stats, &parser, numbers[i_number]);
            i_number = (i_number + 1) % numbers.size();
            player->start();
            _add_peer(player);
        } catch (NetworkError& e) {
            break;
        }
        _remove_dead();
    }

    for (size_t i = 0; i < players.size(); i++) {
        players[i]->join();
        delete players[i];
    }
}

void GameServer::run() {
    try {
        numbers = std::move(parser.parse_numbers());
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    std::thread acceptor_thread(&GameServer::_accept_connections, this);
    std::string buffer;
    while (std::getline(std::cin, buffer)) {
        if (buffer == QUIT_STR) {
            server.stop_listening();
            break;
        }
    }

    acceptor_thread.join();
    stats.print_stats();
}
