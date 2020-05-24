#ifndef __COMMAND_HELP_H
#define __COMMAND_HELP_H

/* ------ Includes ---------*/
#include <vector>
#include "client_command.h"

/* ------ Interfaz ---------*/
class CommandHelp : public Command {
   public:
    CommandHelp();
    ~CommandHelp();

    /* Devuelve la serializacion correspondiente al comando. */
    virtual std::vector<std::uint8_t> get_serialization() override;
};

#endif
