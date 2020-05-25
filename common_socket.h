#ifndef __SOCKET_H
#define __SOCKET_H

/* ------ Includes ---------*/
#include <cstdint>
#include <vector>

/* ------ Interfaz ---------*/
class Socket {
   protected:
    int skt;
    bool is_server;

    /* Obtiene la informacion DNS necesaria para establecer la conexion
    y la almacena en result.*/
    void _get_dns_info(const char* host, const char* port,
                       struct addrinfo** result,bool is_server);

    /* Establece la conexion al primer resultado valido dentro de la lista
    de resultados.*/
    void _connect(struct addrinfo* result);

    /* Abre el socket a la escucha de nuevas conexiones.*/
    void _start_listening(struct addrinfo* result);

   public:
    /* Constructor utilizado para crear un socket cliente. Recibe
    un host y un puerto.*/
    Socket(const char* host, const char* port);

    /* Constructor utilizado para crear un socket acceptor (servidor). Recibe
    el puerto donde debe escuchar las conexiones.*/
    explicit Socket(const char* port);

    /* Constructor utilizado para crear un socket a partir de un
    file descriptor ya inicializado.*/
    explicit Socket(int skt);

    /* Acepta una nueva conexion y devuelve el socket que representa
    la conexion con el nuevo cliente.*/
    Socket accept_connection();

    ~Socket();

    /* Envia un mensaje a traves del socket. Para el tamanio del mensaje
    se utiliza el size() del vector.*/
    size_t send_message(const std::vector<uint8_t>& message);

    /* Recibe un mensaje de tamanio msgsize.*/
    std::vector<uint8_t> recieve_message(size_t msgsize);
    
    /* Cierra el socket. */
    void close_connection();

    /* Anulado el constructor por copia. */
    Socket(const Socket& other) = delete;

    /* Constructor por movimiento. */
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);
};

#endif
