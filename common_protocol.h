#ifndef __PROTOCOL_H
#define __PROTOCOL_H

/* ------ Includes ---------*/
#include <string>
#include "common_network_error.h"
#include "common_socket.h"

/* ------ Interfaz ---------*/
class Protocol {
   public:
    Protocol();
    ~Protocol();

    std::string receive_string(Socket &socket);

    /* Recibe un caracter a traves del socket. */
    uint8_t receive_char(Socket &socket);

    /* Recibe un entero no signado de 2 bytes a traves del socket. */
    uint16_t receive_int(Socket &socket);

    /* Envia una string a traves del socket. */
    void send_string(Socket &socket, const std::string str);
};

#endif
