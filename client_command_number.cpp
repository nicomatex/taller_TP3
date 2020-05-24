#include <arpa/inet.h>
#include <cstring>

#include "client_command_number.h"
#include "client_config.h"
#include "common_config.h"

std::vector<uint8_t> CommandNumber::get_serialization() {
    std::vector<uint8_t> buffer;
    buffer.reserve(CMD_NUMBER_SIZE);
    buffer.push_back(SERIAL_CHAR_NUMBER);

    uint16_t number = htons(this->number);

    buffer.resize(CMD_NUMBER_SIZE);
    std::memcpy(&buffer[CMD_NUMBER_NUMPOS], &number, sizeof(uint16_t));

    return buffer;
}

CommandNumber::CommandNumber(uint16_t number) : number(number) {}

CommandNumber::~CommandNumber() {}