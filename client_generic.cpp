#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "client_game.h"
#include "common_config.h"
#include "common_network_error.h"

void Client::_get_dns_info(const char* host, const char* port,
                           struct addrinfo** result) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    if (getaddrinfo(host, port, &hints, result) != 0) {
        throw NetworkError(ERROR_MSG_DNS);
    }
}

void Client::_connect(struct addrinfo* result) {
    struct addrinfo* current;
    bool is_connected = false;
    int socket_state = 0;
    int tmp_skt = 0;

    for (current = result; current != NULL && !is_connected;
         current = current->ai_next) {
        tmp_skt = socket(current->ai_family, current->ai_socktype,
                         current->ai_protocol);
        if (tmp_skt == -1) {
            std::cerr << "Error: " << strerror(errno) << std::endl;
        } else {
            socket_state =
                connect(tmp_skt, current->ai_addr, current->ai_addrlen);
            if (socket_state == -1) {
                std::cerr << "Error: " << strerror(errno) << std::endl;
                close(tmp_skt);
            }
            is_connected = (socket_state != -1);
        }
    }
    if (!is_connected) {
        throw NetworkError(ERROR_MSG_CONNECTION);
    }
    skt.set_socketfd(tmp_skt);
}

size_t Client::send_message(const std::vector<uint8_t>& message) {
    return skt.send_message(message);
}

std::vector<uint8_t> Client::recieve_message(size_t msgsize) {
    return skt.recieve_message(msgsize);
}

Client::Client(const char* host, const char* port) {
    struct addrinfo* result;
    _get_dns_info(host, port, &result);
    try {
        _connect(result);
    } catch (NetworkError& e) {
        free(result);
        throw;
    }
    free(result);
}

Socket* Client::get_socket(){
    return &skt;
}

Client::Client(Client&& other) { this->skt = std::move(other.skt); }

Client& Client::operator=(Client&& other) {
    this->skt = std::move(other.skt);
    return *this;
}

Client::~Client() { skt.close_connection(); }
