#include <thread>
#include <iostream>
#include <string>
#include "server_game.h"
#include "common_error.h"

GameServer::GameServer(const char* port, const char* numbers_file)
    : server(port),accepting_connections(true) {}

GameServer::~GameServer(){}

void GameServer::_add_peer(PlayerHandler* player){
    std::unique_lock<std::mutex> l(m);
    players.push_back(player);
}

void GameServer::_accept_connections(){
    while(accepting_connections){
        try{

        Socket peer = std::move(server.accept_connection());
        PlayerHandler* player = new PlayerHandler(std::move(peer));
        player->start();
        _add_peer(player);
        }catch(Error &e){
            break;
        }
        /* Remover muertos aca */
    }
    for(size_t i = 0;i<players.size();i++){
        players[i]->stop();
        players[i]->join();
        delete players[i];
    }
}

void GameServer::run(){
    std::thread acceptor_thread(&GameServer::_accept_connections,this);
    std::string buffer;
    while(std::getline(std::cin,buffer)){
        if(buffer == "q"){
            server.stop_listening();
            break;
        }
    }

    acceptor_thread.join();
}