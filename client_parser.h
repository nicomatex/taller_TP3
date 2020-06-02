#ifndef __CLIENT_PARSER_H
#define __CLIENT_PARSER_H

/* ------ Includes ------*/
#include <iostream>
#include <string>
#include "common_command.h"
#include "common_number_parser.h"

/* ------ Interfaz ---------*/
class ClientParser {
   private:
    NumberParser number_parser;

   public:
    ClientParser();
    ~ClientParser();

    /* Parsea una linea y devuelve el comando correspondiente
    a la linea parseada. Siempre devuelve un comando valido.*/
    Command* operator()();
};

#endif
