#ifndef __SOCKET_H
#define __SOCKET_H

#include <vector>
#include <cstdint>

class Socket{
    protected:
        int skt;
    public:
        Socket();
        ~Socket();

        /* Envia un mensaje a traves del socket. Para el tamanio del mensaje
        se utiliza el size() del vector.*/
        size_t send_message(const std::vector<uint8_t> &message);

        /* Recibe un mensaje de tamanio msgsize.*/
        std::vector<uint8_t> recieve_message(size_t msgsize);

        /* Setea el File Descriptor asociado al socket.*/
        void set_socketfd(int socketfd);

        /* Cierra el socket. */
        void close_connection();
        
        /* Anulado el constructor por copia. */
        Socket(const Socket &other) = delete;

        /* Constructor por movimiento. */
        Socket(Socket&& other);
        Socket& operator=(Socket&& other);
};

#endif