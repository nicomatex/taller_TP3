#ifndef __CLIENT_CONFIG_H
#define __CLIENT_CONFIG_H

/* Cantidad de argumentos */
#define CLIENT_ARG_QTY 3

/* Comandos de entrada */
#define CMD_HELP "AYUDA"
#define CMD_SURRENDER "RENDIRSE"

/* Mensajes que provienen del servidor */
#define RESP_LOSE "Perdiste"
#define RESP_WIN "Ganaste"

/* Textos de la interfaz */
#define INVALID_CMD "Error: comando inválido. Escriba AYUDA para obtener ayuda"

/* Tamanio y posicion donde se ubica el numero en la serializacion del comando
 * numero*/
#define CMD_NUMBER_SIZE 3
#define CMD_NUMBER_NUMPOS 1

/* Errores */
#define MSG_ERR_UNKNOWN "Ocurrio un error inesperado."
#define MSG_ERR_PARAMS "Error: argumentos invalidos."

/* Argumentos */
#define ARG_POS_HOST 1
#define ARG_POS_PORT 2

/* Limites de entrada */
#define MAX_NUMBER_LENGTH 6
#endif
