#include "server_acceptor_socket.h"
#include "server_config.h"
#include "common_error.h"

#include <sys/socket.h>
#include <sys/types.h>

Socket AcceptorSocket::accept_connection(){
    Socket new_connection;
    int temp_socketfd = accept(this->skt,NULL,NULL);
    if(temp_socketfd == -1){
        throw Error(MSG_ERR_PEER);
    }
    new_connection.set_socketfd(temp_socketfd);
    return new_connection;
}