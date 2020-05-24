#ifndef __COMMAND_SURRENDER_H
#define __COMMAND_SURRENDER_H

/* ------ Includes ---------*/
#include <vector>
#include "client_command.h"

/* ------ Interfaz ---------*/
class CommandSurrender : public Command {
   public:
    CommandSurrender();
    ~CommandSurrender();

    /* Devuelve la serializacion correspondiente al comando. */
    virtual std::vector<std::uint8_t> get_serialization() override;
};

#endif
