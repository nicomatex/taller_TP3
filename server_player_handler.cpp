#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "server_player_handler.h"
#include "arpa/inet.h"
#include "common_config.h"
#include "common_network_error.h"
#include "server_config.h"

PlayerHandler::PlayerHandler(Socket peer, Statistics* stats,
                             NumberParser* parser, const uint16_t guess_number)
    : stats(stats),
      parser(parser),
      protocol(std::move(peer)),
      is_dead(false),
      guess_number(guess_number),
      tries_left(TRIES_MAX),
      player_won(false) {}

bool PlayerHandler::dead() { return is_dead; }

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

    if (n_right > 0) {
        hints += std::to_string(n_right) + " " + MSG_RIGHT;
    }
    if (n_regular > 0) {
        if (n_right > 0) hints += ", ";
        hints += std::to_string(n_regular) + " " + MSG_REGULAR;
    }
    if (n_right == 0 && n_regular == 0) {
        hints += std::to_string(number_string.size()) + " " + MSG_WRONG;
    }
    return hints;
}

void PlayerHandler::_handle_help() { protocol.send_string(MSG_HELP); }

void PlayerHandler::_handle_surrender() {
    protocol.send_string(MSG_LOSE);
    stop();
}

void PlayerHandler::_handle_number() {
    uint16_t number = protocol.receive_int();

    /* Chequeo de validez del numero */
    if (!parser->is_within_range(number) ||
        parser->has_repeated_digits(std::to_string((int)number))) {
        tries_left--;
        if (tries_left == 0) {
            protocol.send_string(MSG_LOSE);
        } else {
            protocol.send_string(MSG_WRONG_NUMBER);
        }
        return;
    }

    /* Chequeo de que haya adivinado el numero. */
    if (number == guess_number) {
        protocol.send_string(MSG_WIN);
        player_won = true;
        return;
    }

    tries_left--;
    if (tries_left == 0) {
        protocol.send_string(MSG_LOSE);
    } else {
        protocol.send_string(_get_hints(number));
    }
}

void PlayerHandler::run() {
    while (!player_won && tries_left > 0 && !is_dead) {
        try {
            uint8_t command = protocol.receive_char();

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
        } catch (NetworkError& e) {
            break;
        }
    }
    if (!is_dead) {
        stop();
    }
    if (player_won) {
        stats->add_winner();
    } else {
        stats->add_loser();
    }
}

void PlayerHandler::stop() {
    std::unique_lock<std::mutex> l(m);
    protocol.close_connection();
    is_dead = true;
}
