#include <sys/socket.h>
#include <sys/types.h>

#include "server_acceptor_socket.h"
#include "common_network_error.h"
#include "server_config.h"

Socket AcceptorSocket::accept_connection() {
    Socket new_connection;
    int temp_socketfd = accept(this->skt, NULL, NULL);
    if (temp_socketfd == -1) {
        throw NetworkError(MSG_ERR_PEER);
    }
    new_connection.set_socketfd(temp_socketfd);
    return new_connection;
}
