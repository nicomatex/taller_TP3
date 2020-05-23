#include "server_player_handler.h"
#include <iostream> //debug
#include "common_error.h"

PlayerHandler::PlayerHandler(Socket peer)
    : peer(std::move(peer)), is_dead(false) {}

void PlayerHandler::run(){
    std::cout << "DEBUG: Nuevo cliente conectado! " << std::endl;
    while(true){
        try{
        std::vector<uint8_t> received = std::move(peer.recieve_message(1));
        if(received.size() == 0) break;    
        std::cout << received[0] << std::endl;
        }catch(Error &e){
            break;
        }
    }
    std::cout << "DEBUG: Conexion con un cliente cerrada." << std::endl;
    is_dead = true;
}

void PlayerHandler::stop(){
    std::unique_lock<std::mutex> l(m);
    if(!is_dead){
        peer.close_connection();   
        is_dead = true;
    }
}