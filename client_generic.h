#ifndef __CLIENT_H
#define __CLIENT_H

/* ------ Includes ---------*/
#include <cstdint>
#include <string>
#include <vector>
#include "common_socket.h"


struct addrinfo;

/* ------ Interfaz ---------*/
class Client {
   private:
    Socket skt;
    /* Utilizada por la clase para obtener la informacion DNS para el
    host y puerto indicados.*/
    void _get_dns_info(const char* host, const char* port,
                       struct addrinfo** result);

    /* Utilizada por la clase para establecer la conexion al
    servidor.*/
    void _connect(struct addrinfo* result);

   public:
    Client(const char* host, const char* port);
    ~Client();

    /* Envia un mensaje a traves del socket. Para el tamanio del mensaje
        se utiliza el size() del vector.*/
    size_t send_message(const std::vector<uint8_t>& message);

    /* Recibe un mensaje de tamanio msgsize.*/
    std::vector<uint8_t> recieve_message(size_t msgsize);

    /* Devuelve un puntero al socket*/
    Socket* get_socket();

    /* Anulada la construccion por copia. */
    Client(const Client& other) = delete;

    /* Constructor por movimiento. */
    Client(Client&& other);
    Client& operator=(Client&& other);
};

#endif
