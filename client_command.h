#ifndef __COMMAND_H
#define __COMMAND_H

#include <cstdint>
#include <vector>

class Command{
    public:
        virtual std::vector<std::uint8_t> get_serialization() = 0;
        virtual ~Command(){}
};

#endif