#include "client_parser.h"

#include <iostream>
#include <iomanip>
int main(void){
    ClientParser parser;
    Command* comando_parseado;
    comando_parseado = parser();
    std::vector<uint8_t> serializado = comando_parseado->get_serialization();
    for(size_t i = 0;i<serializado.size();i++){
        std::cout  << std::setw(2) << std::setfill('0') << std::hex << (int)serializado[i] << " ";
    }
    std::cout << std::endl;
    delete comando_parseado;
    return 0;
}