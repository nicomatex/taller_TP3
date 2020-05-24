#include <cstring>
#include <arpa/inet.h>
#include "common_protocol.h"
#include "common_config.h"

Protocol::Protocol(Socket *socket):socket(socket){}

Protocol::~Protocol(){}

std::string Protocol::receive_string() {
    std::vector<uint8_t> res_size_buffer =
        std::move(socket->recieve_message(sizeof(uint16_t)));

    uint16_t res_size = 0;
    memcpy(&res_size, &res_size_buffer[0], sizeof(uint16_t));

    res_size = ntohs(res_size);

    std::vector<uint8_t> res_buffer =
        std::move(socket->recieve_message((size_t)res_size));
    std::string response;

    for (size_t i = 0; i < res_buffer.size(); i++) {
        response.push_back((char)res_buffer[i]);
    }

    return response;
}

void Protocol::send_string(const std::string str) {
    uint16_t length = (uint16_t)str.length();
    length = htons(length);  // Pasaje a big endian

    std::vector<uint8_t> output_buffer;
    output_buffer.resize(sizeof(uint16_t) + str.length());
    memcpy(&output_buffer[0], &length, sizeof(uint16_t));
    memcpy(&output_buffer[sizeof(uint16_t)], &str[0], str.length());

    socket->send_message(output_buffer);
}

uint8_t Protocol::receive_char() {
    std::vector<uint8_t> in_buffer = std::move(socket->recieve_message(1));
    if (in_buffer.size() == 0) {
        throw NetworkError(MSG_ERR_CLOSED);
    }
    uint8_t command = in_buffer[0];
    return command;
}

uint16_t Protocol::receive_int() {
    std::vector<uint8_t> in_buffer = std::move(socket->recieve_message(2));
    if (in_buffer.size() == 0) {
        throw NetworkError(MSG_ERR_CLOSED);
    }
    uint16_t number = 0;
    memcpy(&number, &in_buffer[0], sizeof(uint16_t));
    number = ntohs(number);  // Pasaje a little endian
    return number;
}
