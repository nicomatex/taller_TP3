#ifndef __NUMBER_PARSER_H
#define __NUMBER_PARSER_H

/* ------ Includes ---------*/
#include <cstdint>
#include <string>
#include <vector>

/* ------ Interfaz ---------*/
class NumberParser {
   private:
    const char* filename;
    bool _is_number(const std::string& s);

   public:
    /* Recibe una cadena s y devuelve true si contiene
    digitos repetidos, false en caso contrario. */
    bool has_repeated_digits(const std::string& s);

    /* Recibe un numero number y devuelve true si esta 
    dentro del rango definido para el juego.*/
    bool is_within_range(uint16_t number);

    /* Parsea los numeros en el archivo pasado en el constructor
    y los devuelve en un vector.*/
    std::vector<uint16_t> parse_numbers();

    explicit NumberParser(const char* filename);

    ~NumberParser();
};

#endif
