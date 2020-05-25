#ifndef __COMMAND_H
#define __COMMAND_H

/* ------ Includes ---------*/
#include <cstdint>
#include <vector>

/* ------ Interfaz ---------*/
class Command {
   public:
    /* Metodo que las clases hijas deben implementar. Devuelve la serializacion
     * del comando*/
    virtual std::vector<std::uint8_t> get_serialization() = 0;
    virtual ~Command() {}
};

#endif
