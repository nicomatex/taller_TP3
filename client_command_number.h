#ifndef __COMMAND_NUMBER_H
#define __COMMAND_NUMBER_H

#include "client_command.h"

class CommandNumber : public Command {
   private:
    uint16_t number;
   public:
    CommandNumber(uint16_t number);
    ~CommandNumber();

     /* Devuelve la serializacion correspondiente al comando. */
    virtual std::vector<std::uint8_t> get_serialization() override;
};

#endif