#ifndef __SERVER_CONFIG_H
#define __SERVER_CONFIG_H

/* Errores*/
#define MSG_ERR_FILE "Error abriendo el archivo."
#define MSG_ERR_NOTANUMBER "Linea no numerica encontrada."
#define MSG_ERR_REPEATED "Error: formato de los números inválidos"
#define MSG_ERR_RANGE "Error: archivo con números fuera de rango"
#define MSG_ERR_LISTEN "Error abriendo el servidor en el puerto indicado."
#define MSG_ERR_PEER "Error: No se pudo aceptar la conexion entrante."

/* Parametros del juego*/
#define NUMBER_MIN 100
#define NUMBER_MAX 999


/* Parametros del servidor */
#define CLIENT_QUEUE_SIZE 20

#endif