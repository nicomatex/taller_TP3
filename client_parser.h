#ifndef __CLIENT_PARSER_H
#define __CLIENT_PARSER_H

/* ------ Includes ------*/
#include <iostream>
#include <string>
#include "common_command.h"

/* ------ Interfaz ---------*/
class ClientParser {
   private:
    bool _is_number(const std::string& s);

   public:
    ClientParser();
    ~ClientParser();

    /* Parsea una linea y devuelve el comando correspondiente
    a la linea parseada. Siempre devuelve un comando valido.*/
    Command* operator()();
};

#endif
