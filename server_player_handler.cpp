#include "server_player_handler.h"

#include <cstring>
#include <iostream>  //debug

#include "arpa/inet.h"
#include "common_config.h"
#include "common_error.h"
#include "server_config.h"

PlayerHandler::PlayerHandler(Socket peer, Statistics* stats,
                             NumberParser* parser, const uint16_t guess_number)
    : peer(std::move(peer)),
      stats(stats),
      parser(parser),
      is_dead(false),
      guess_number(guess_number),
      tries_left(TRIES_MAX),
      player_won(false) {}

void PlayerHandler::_send_string(const std::string str) {
    uint16_t length = (uint16_t)str.length();
    length = htons(length);  // Pasaje a big endian

    std::vector<uint8_t> output_buffer;
    output_buffer.resize(sizeof(uint16_t) + str.length());
    memcpy(&output_buffer[0], &length, sizeof(uint16_t));
    memcpy(&output_buffer[sizeof(uint16_t)], &str[0], str.length());

    peer.send_message(output_buffer);
}

uint8_t PlayerHandler::_receive_command() {
    std::vector<uint8_t> in_buffer = std::move(peer.recieve_message(1));
    if (in_buffer.size() == 0) {
        throw Error(MSG_ERR_CLOSED);
    }
    uint8_t command = in_buffer[0];
    return command;
}

uint16_t PlayerHandler::_receive_int() {
    std::vector<uint8_t> in_buffer = std::move(peer.recieve_message(2));
    if (in_buffer.size() == 0) {
        throw Error(MSG_ERR_CLOSED);
    }
    uint16_t number = 0;
    memcpy(&number, &in_buffer[0], sizeof(uint16_t));
    number = ntohs(number);  // Pasaje a little endian
    return number;
}

std::string PlayerHandler::_get_hints(uint16_t number) {
    unsigned int n_right = 0;
    unsigned int n_regular = 0;
    std::string guess_number_string = std::to_string((int)guess_number);
    std::string number_string = std::to_string((int)number);

    for (size_t i = 0; i < number_string.length(); i++) {
        if (guess_number_string[i] == number_string[i]) {
            n_right++;
        } else if (guess_number_string.find(number_string[i]) !=
                   std::string::npos) {
            n_regular++;
        }
    }

    std::string hints = "";
    
    if(n_right > 0){
        hints += std::to_string(n_right) + " " + KEYWORD_RIGHT;
    }
    if(n_regular > 0){
        if(n_right > 0) hints += ", ";
        hints += std::to_string(n_regular) + " " + KEYWORD_REGULAR;
    }
    if(n_right == 0 && n_regular == 0){
        hints += std::to_string(number_string.size()) + " " + KEYWORD_WRONG;
    }
    return hints;
}

void PlayerHandler::_handle_help() {
    std::cout << "[DEBUG] El cliente pidio ayuda" << std::endl;
    _send_string(MSG_HELP);
}

void PlayerHandler::_handle_surrender() {
    std::cout << "[DEBUG] El cliente se rindio" << std::endl;
    _send_string(MSG_LOSE);
    stop();
}

void PlayerHandler::_handle_number() {
    uint16_t number = _receive_int();
    std::cout << "[DEBUG] Recibido: " << std::to_string((int)number)
              << std::endl;

    /* Chequeo de validez del numero */
    if (!parser->is_within_range(number) ||
        parser->has_repeated_digits(std::to_string((int)number))) {
        tries_left--;
        if (tries_left == 0) {
            _send_string(MSG_LOSE);
        } else {
            _send_string(MSG_WRONG_NUMBER);
        }
        return;
    }

    /* Chequeo de que haya adivinado el numero. */
    if (number == guess_number) {
        _send_string(MSG_WIN);
        player_won = true;
        return;
    }

    tries_left--;
    if(tries_left == 0){
        _send_string(MSG_LOSE);
    }else{
        _send_string(_get_hints(number));
    }
}

void PlayerHandler::run() {
    std::cout << "[DEBUG] Nuevo cliente conectado, jugando con el numero "
              << std::to_string((int)guess_number) << std::endl;

    while (!player_won && tries_left > 0 && !is_dead) {
        try {
            uint8_t command = _receive_command();

            switch (command) {
                case SERIAL_CHAR_HELP:
                    _handle_help();
                    break;
                case SERIAL_CHAR_SURRENDER:
                    _handle_surrender();
                    break;
                case SERIAL_CHAR_NUMBER:
                    _handle_number();
                    break;
                default:
                    continue;
            }
        } catch (Error& e) {
            break;
        }
    }
    if (!is_dead) {
        stop();
    }
    std::cout << "[DEBUG] Conexion con un cliente cerrada." << std::endl;
}

void PlayerHandler::stop() {
    std::unique_lock<std::mutex> l(m);
    peer.close_connection();
    is_dead = true;
}