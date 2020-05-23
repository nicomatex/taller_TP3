#include "server_generic.h"

#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>

#include "common_config.h"
#include "common_error.h"
#include "server_config.h"

void Server::_get_dns_info(const char* host, const char* port,
                           struct addrinfo** result) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(host, port, &hints, result) != 0) {
        throw Error(ERROR_MSG_DNS);
    }
}

void Server::_start_listening(struct addrinfo* result) {
    int tmp_skt =
        socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (tmp_skt == -1) {
        throw Error(MSG_ERR_LISTEN);
    }

    int val = 1;

    /* Establece SO_REUSEADDR para utilizar inmediatamente el socket.*/
    if (setsockopt(tmp_skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) ==
        -1) {
        close(tmp_skt);
        throw Error(MSG_ERR_LISTEN);
    }

    if (bind(tmp_skt, result->ai_addr, result->ai_addrlen) == -1) {
        close(tmp_skt);
        throw Error(MSG_ERR_LISTEN);
    }

    if (listen(tmp_skt, CLIENT_QUEUE_SIZE) == -1) {
        close(tmp_skt);
        throw Error(MSG_ERR_LISTEN);
    }
    acceptor_skt.set_socketfd(tmp_skt);
}

Server::Server(const char* port) {
    struct addrinfo* result;
    _get_dns_info(NULL, port, &result);

    try {
        _start_listening(result);
    } catch (Error& e) {
        free(result);
        throw;
    }
    free(result);
}

Socket Server::accept_connection() { return acceptor_skt.accept_connection(); }

void Server::stop_listening(){
    acceptor_skt.close_connection();
}

Server::~Server() {}