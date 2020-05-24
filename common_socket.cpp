#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <utility>

#include "common_socket.h"
#include "common_config.h"
#include "common_network_error.h"

size_t Socket::send_message(const std::vector<uint8_t>& message) {
    size_t total_sent = 0;
    int just_sent = 0;
    bool valid_socket = true;

    while (total_sent < message.size() && valid_socket) {
        just_sent =
            send(skt, &message[0], message.size() - total_sent, MSG_NOSIGNAL);
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
        throw NetworkError(ERROR_MSG_SEND);
    }
}

std::vector<uint8_t> Socket::recieve_message(size_t msgsize) {
    std::vector<uint8_t> buffer(msgsize);

    bool socket_error = false;
    bool remote_socket_closed = false;

    size_t total_received = 0;
    int just_received = 0;

    while (total_received < msgsize && !socket_error && !remote_socket_closed) {
        just_received =
            recv(skt, &buffer[total_received], msgsize - total_received, 0);
        if (just_received == -1) {
            throw NetworkError(ERROR_MSG_RECEIVE);
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

void Socket::set_socketfd(int socketfd) { skt = socketfd; }

void Socket::close_connection() {
    shutdown(skt, SHUT_RDWR);
    close(skt);
}

Socket::Socket() : skt(0) {}

Socket::Socket(Socket&& other) { this->skt = std::move(other.skt); }

Socket& Socket::operator=(Socket&& other) {
    this->skt = std::move(other.skt);
    return *this;
}

Socket::~Socket() {}
