#ifndef __COMMAND_SURRENDER_H
#define __COMMAND_SURRENDER_H

#include "client_command.h"

class CommandSurrender : public Command {
   public:
    CommandSurrender();
    ~CommandSurrender();

    /* Devuelve la serializacion correspondiente al comando. */
    virtual std::vector<std::uint8_t> get_serialization() override;
};

#endif