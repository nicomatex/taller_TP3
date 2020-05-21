#ifndef __CLIENT_PARSER_H
#define __CLIENT_PARSER_H

/* ------ Includes ------*/
#include <iostream>
#include <string>
#include "client_command.h"

class ClientParser {
   private:
    bool _is_number(const std::string &s);
   public:
    ClientParser();
    ~ClientParser();
    Command* operator()();
};

#endif