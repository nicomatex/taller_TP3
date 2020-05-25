#ifndef __SERVER_CONFIG_H
#define __SERVER_CONFIG_H

/* Errores*/
#define MSG_ERR_FILE "Error abriendo el archivo."
#define MSG_ERR_NOTANUMBER "Linea no numerica encontrada."
#define MSG_ERR_REPEATED "Error: formato de los números inválidos"
#define MSG_ERR_RANGE "Error: archivo con números fuera de rango"
#define MSG_ERR_ARGS "Error: argumentos invalidos."

/* Interfaz del servidor */
#define QUIT_STR "q"

/* Respuestas al cliente */
#define MSG_HELP                                                              \
    "Comandos válidos:\n\tAYUDA: despliega la lista de comandos "             \
    "válidos\n\tRENDIRSE: pierde el juego automáticamente\n\tXXX: Número de " \
    "3 cifras a ser enviado al servidor para adivinar el número secreto"

#define MSG_LOSE "Perdiste"
#define MSG_WIN "Ganaste"
#define MSG_WRONG_NUMBER "Número inválido. Debe ser de 3 cifras no repetidas"

#define MSG_RIGHT "bien"
#define MSG_REGULAR "regular"
#define MSG_WRONG "mal"
#define MSG_STATS "Estadísticas"
#define MSG_WINNERS "Ganadores"
#define MSG_LOSERS "Perdedores"

/* Parametros del juego*/
#define NUMBER_MIN 100
#define NUMBER_MAX 999
#define TRIES_MAX 10

/* Argumentos del programa */
#define ARGS_QTY 3
#define ARG_POS_PORT 1
#define ARG_POS_NUMBERFILE 2

#endif
