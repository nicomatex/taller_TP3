#include "common_protocol.h"

#include <arpa/inet.h>

#include <cstring>
#include <utility>
#include <vector>

#include "common_config.h"

Protocol::Protocol(Socket socket) : socket(std::move(socket)) {}

Protocol::~Protocol() {}

std::string Protocol::receive_string() {
    std::vector<uint8_t> res_size_buffer =
        std::move(socket.recieve_message(sizeof(uint32_t)));

    uint32_t res_size = 0;
    *(&res_size) = *((uint32_t*)(&res_size_buffer[0]));

    res_size = ntohs(res_size);

    std::vector<uint8_t> res_buffer =
        std::move(socket.recieve_message((size_t)res_size));

    if (res_buffer.size() == 0) {
        throw NetworkError(MSG_ERR_CLOSED);
    }

    std::string response(res_buffer.begin(),res_buffer.end());

    return response;
}

void Protocol::send_string(const std::string str) {
    uint32_t length = (uint32_t)str.length();
    length = htons(length);  // Pasaje a big endian

    std::vector<uint8_t> output_buffer;
    output_buffer.resize(sizeof(uint32_t) + str.length());
    memcpy(&output_buffer[0], &length, sizeof(uint32_t));
    memcpy(&output_buffer[sizeof(uint32_t)], &str[0], str.length());

    socket.send_message(output_buffer);
}

uint8_t Protocol::receive_char() {
    std::vector<uint8_t> in_buffer = std::move(socket.recieve_message(1));
    if (in_buffer.size() == 0) {
        throw NetworkError(MSG_ERR_CLOSED);
    }
    uint8_t command = in_buffer[0];
    return command;
}

uint16_t Protocol::receive_int() {
    std::vector<uint8_t> in_buffer =
        std::move(socket.recieve_message(sizeof(uint16_t)));

    if (in_buffer.size() == 0) {
        throw NetworkError(MSG_ERR_CLOSED);
    }
    uint16_t number = 0;
    *(&number) = *((uint16_t*)(&in_buffer[0]));

    number = ntohs(number);  // Pasaje a little endian
    return number;
}

void Protocol::close_connection() { socket.close_connection(); }

void Protocol::send_command(Command *command) {
    socket.send_message(command->get_serialization());
}
