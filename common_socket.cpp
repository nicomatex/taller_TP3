#include "common_socket.h"

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <utility>

#include "common_config.h"
#include "common_network_error.h"

Socket::Socket(const char* host, const char* port) : is_server(false) {
    struct addrinfo* result;
    _get_dns_info(host, port, &result, false);
    try {
        _connect(result);
    } catch (NetworkError& e) {
        free(result);
        throw;
    }
    free(result);
}

Socket::Socket(const char* port) : is_server(true) {
    struct addrinfo* result;
    _get_dns_info(NULL, port, &result, true);

    try {
        _start_listening(result);
    } catch (NetworkError& e) {
        free(result);
        throw;
    }
    free(result);
}

Socket::Socket(int skt) : skt(skt), is_server(false) {}

Socket Socket::accept_connection() {
    if (!is_server) {
        throw NetworkError(MSG_ERR_WRONGSOCKET);
    }
    int temp_socketfd = accept(this->skt, NULL, NULL);
    if (temp_socketfd == -1) {
        throw NetworkError(MSG_ERR_PEER);
    }
    return Socket(temp_socketfd);
}

void Socket::_get_dns_info(const char* host, const char* port,
                           struct addrinfo** result, bool is_server) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = is_server ? AI_PASSIVE : 0;

    if (getaddrinfo(host, port, &hints, result) != 0) {
        throw NetworkError(MSG_ERR_DNS);
    }
}

void Socket::_connect(struct addrinfo* result) {
    struct addrinfo* current;
    bool is_connected = false;
    int socket_state = 0;
    int tmp_skt = 0;

    for (current = result; current != NULL && !is_connected;
         current = current->ai_next) {
        tmp_skt = socket(current->ai_family, current->ai_socktype,
                         current->ai_protocol);
        if (tmp_skt != -1) {
            socket_state =
                connect(tmp_skt, current->ai_addr, current->ai_addrlen);
            if (socket_state == -1) {
                close(tmp_skt);
            }
            is_connected = (socket_state != -1);
        }
    }
    if (!is_connected) {
        throw NetworkError(MSG_ERR_CONNECTION);
    }
    skt = tmp_skt;
}

void Socket::_start_listening(struct addrinfo* result) {
    int tmp_skt =
        socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (tmp_skt == -1) {
        throw NetworkError(MSG_ERR_LISTEN);
    }

    int val = 1;

    /* Establece SO_REUSEADDR para utilizar inmediatamente el socket.*/
    if (setsockopt(tmp_skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) ==
        -1) {
        close(tmp_skt);
        throw NetworkError(MSG_ERR_LISTEN);
    }

    if (bind(tmp_skt, result->ai_addr, result->ai_addrlen) == -1) {
        close(tmp_skt);
        throw NetworkError(MSG_ERR_LISTEN);
    }

    if (listen(tmp_skt, CLIENT_QUEUE_SIZE) == -1) {
        close(tmp_skt);
        throw NetworkError(MSG_ERR_LISTEN);
    }
    skt = tmp_skt;
}

size_t Socket::send_message(const std::vector<uint8_t>& message) {
    if (is_server) {
        throw NetworkError(MSG_ERR_WRONGSOCKET);
    }
    size_t total_sent = 0;
    int just_sent = 0;
    bool valid_socket = true;

    while (total_sent < message.size() && valid_socket) {
        just_sent = send(skt, &message[total_sent], message.size() - total_sent,
                         MSG_NOSIGNAL);
        if (just_sent == 0) return 0;

        if (just_sent == -1) {
            valid_socket = false;
        } else {
            total_sent += (size_t)just_sent;
        }
    }
    if (valid_socket) {
        return total_sent;
    } else {
        throw NetworkError(MSG_ERR_SEND);
    }
}

std::vector<uint8_t> Socket::recieve_message(size_t msgsize) {
    if (is_server) {
        throw NetworkError(MSG_ERR_WRONGSOCKET);
    }
    std::vector<uint8_t> buffer(msgsize);

    bool socket_error = false;
    bool remote_socket_closed = false;

    size_t total_received = 0;
    int just_received = 0;

    while (total_received < msgsize && !socket_error && !remote_socket_closed) {
        just_received =
            recv(skt, &buffer[total_received], msgsize - total_received, 0);
        if (just_received == -1) {
            throw NetworkError(MSG_ERR_RECEIVE);
        } else if (just_received == 0) {
            remote_socket_closed = true;
        }
        total_received += (size_t)just_received;
    }
    if (!remote_socket_closed) {
        buffer.resize(total_received);
    } else {
        buffer.resize(0);
    }

    return buffer;
}

void Socket::close_connection() {
    shutdown(skt, SHUT_RDWR);
    close(skt);
}

Socket::Socket(Socket&& other) {
    this->skt = std::move(other.skt);
    this->is_server = std::move(other.is_server);
}

Socket& Socket::operator=(Socket&& other) {
    this->skt = std::move(other.skt);
    this->is_server = std::move(other.is_server);
    return *this;
}

Socket::~Socket() {}
