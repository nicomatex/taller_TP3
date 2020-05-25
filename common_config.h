#ifndef __COMMON_CONFIG_H
#define __COMMON_CONFIG_H

/* Errores relacionados a la red. */
#define MSG_ERR_DNS "Error obteniendo la informacion DNS."
#define MSG_ERR_CONNECTION "Error conectandose al servidor."
#define MSG_ERR_SEND "Error enviando el mensaje."
#define MSG_ERR_RECEIVE "Error recibiendo el mensaje."
#define MSG_ERR_CLOSED "Conexion cerrada inesperadamente."
#define MSG_ERR_LISTEN "Error abriendo el servidor en el puerto indicado."
#define MSG_ERR_PEER "Error: No se pudo aceptar la conexion entrante."
#define MSG_ERR_WRONGSOCKET \
    "Error: Este tipo de socket no acepta esta operacion."

/* Caracteres utilizados en la serializacion*/
#define SERIAL_CHAR_HELP 'h'
#define SERIAL_CHAR_SURRENDER 's'
#define SERIAL_CHAR_NUMBER 'n'

/* Parametros del servidor */
#define CLIENT_QUEUE_SIZE 20

#endif
