#include "server_parser.h"
#include "common_error.h"
#include "server_config.h"
#include <iostream>
#include <fstream>
#include <exception>


NumberParser::NumberParser(const char* filename):filename(filename){}

NumberParser::~NumberParser(){}

bool NumberParser::_is_number(const std::string &s) {
    for(size_t i = 0;i<s.length();i++){
        if(!std::isdigit(s[i])) return false;
    }
    return true;
}

bool NumberParser::_has_repeated_digits(const std::string &s){
    int digits[256] = {0};
    for(size_t i = 0;i<s.size();i++){
        if(digits[(int)s[i]] > 0){
            return true;
        }
        digits[(int)s[i]]++;
    }
    return false;
}

bool NumberParser::_is_within_range(uint16_t number){
    return number <= NUMBER_MAX && number >= NUMBER_MIN;
}

std::vector<uint16_t> NumberParser::parse_numbers(){
    std::ifstream input_file(filename);
    if(!input_file.is_open()){
        throw std::ios_base::failure(MSG_ERR_FILE);
    }

    std::string buffer;

    std::vector<uint16_t> numbers;

    while(std::getline(input_file,buffer)){
        if(!_is_number(buffer)){
            throw std::invalid_argument(MSG_ERR_NOTANUMBER);
        }
        if(_has_repeated_digits(buffer)){
            throw std::invalid_argument(MSG_ERR_REPEATED);
        }
        uint16_t number = (uint16_t) std::stoi(buffer);
        if(!_is_within_range(number)){
            throw std::invalid_argument(MSG_ERR_RANGE);
        }
        numbers.push_back(number);
    }
    return numbers;
}