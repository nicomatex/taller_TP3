#include <iostream>
#include "server_parser.h"

int main(void){
    
    NumberParser parser("numeros.txt");
    
    try{
        std::vector<uint16_t> numeros = std::move(parser.parse_numbers());
        for (size_t i = 0; i < numeros.size(); i++)
        {
            std::cout << numeros[i] << std::endl;
        }
        
    }catch(std::invalid_argument &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}