#include <vector>
#include "client_command_surrender.h"
#include "client_config.h"
#include "common_config.h"

std::vector<uint8_t> CommandSurrender::get_serialization() {
    std::vector<uint8_t> buffer;
    buffer.push_back(SERIAL_CHAR_SURRENDER);
    return buffer;
}

CommandSurrender::CommandSurrender() {}

CommandSurrender::~CommandSurrender() {}
