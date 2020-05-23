#include "server_acceptor_socket.h"

class Server {
   private:
    AcceptorSocket acceptor_skt;

    /* Utilizado por la clase para obtener
    la informacion DNS para el host y puerto
    solicitados.*/
    void _get_dns_info(const char* host, const char* port,
                       struct addrinfo** result);

    /* Utilizado para abrir la escucha del servidor a nuevas
    conexiones.*/
    void _start_listening(struct addrinfo* result);

   public:
    /* Recibe el puerto. Abre el servidor para escucha en el momento
    de la construccion. */
    Server(const char* port);
    ~Server();

    /* Cierra el socket aceptador y deja de escuchar nuevas
    conexiones.*/
    void stop_listening();

    /* Acepta una conexion y devuelve un objeto Socket representando
    al peer aceptado.*/
    Socket accept_connection();

};