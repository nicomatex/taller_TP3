#include <exception>
#include <fstream>
#include <iostream>

#include "common_number_parser.h"
#include "common_network_error.h"
#include "server_config.h"

NumberParser::NumberParser(){}

NumberParser::~NumberParser() {}

bool NumberParser::is_number(const std::string &s) {
    for (size_t i = 0; i < s.length(); i++) {
        if (!std::isdigit(s[i])) return false;
    }
    return true;
}

bool NumberParser::has_repeated_digits(const std::string &s) {
    int digits[256] = {0};
    for (size_t i = 0; i < s.size(); i++) {
        if (digits[(int)s[i]] > 0) {
            return true;
        }
        digits[(int)s[i]]++;
    }
    return false;
}

bool NumberParser::is_within_range(uint16_t number) {
    return number <= NUMBER_MAX && number >= NUMBER_MIN;
}

std::vector<uint16_t> NumberParser::parse_number_file(const char* filename) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw std::ios_base::failure(MSG_ERR_FILE);
    }

    std::string buffer;

    std::vector<uint16_t> numbers;

    while (std::getline(input_file, buffer)) {
        if (!is_number(buffer)) {
            throw std::invalid_argument(MSG_ERR_NOTANUMBER);
        }
        if (has_repeated_digits(buffer)) {
            throw std::invalid_argument(MSG_ERR_REPEATED);
        }
        uint16_t number = (uint16_t)std::stoi(buffer);
        if (!is_within_range(number)) {
            throw std::invalid_argument(MSG_ERR_RANGE);
        }
        numbers.push_back(number);
    }
    return numbers;
}
