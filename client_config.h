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

/* Caracteres utilizados en la serializacion*/
#define SERIAL_CHAR_HELP 'h'
#define SERIAL_CHAR_SURRENDER 's'
#define SERIAL_CHAR_NUMBER 'n'

/* Tamanio y posicion donde se ubica el numero en la serializacion del comando
 * numero*/
#define CMD_NUMBER_SIZE 3
#define CMD_NUMBER_NUMPOS 1

/* Errores */
#define MSG_ERR_UNKNOWN "Ocurrio un error inesperado."
#define MSG_ERR_CLOSED "El servidor cerro la conexion."
#define MSG_ERR_PARAMS "Error: argumentos invalidos."
#endif