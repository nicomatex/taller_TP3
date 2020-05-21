#include "client_command_help.h"
#include "client_config.h"

std::vector<uint8_t> CommandHelp::get_serialization(){
    std::vector<uint8_t> buffer;
    buffer.push_back(SERIAL_CHAR_HELP);
    return buffer;
}

CommandHelp::CommandHelp(){}

CommandHelp::~CommandHelp(){}