#ifndef __ACCEPTOR_SOCKET_H
#define __ACCEPTOR_SOCKET_H

#include "common_socket.h"

class AcceptorSocket: public Socket{
    public:
        /* Acepta una nueva conexion entrante y devuelve el objeto
        socket que representa al nuevo cliente. */
        Socket accept_connection();
};

#endif