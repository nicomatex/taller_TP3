#ifndef __NUMBER_PARSER_H
#define __NUMBER_PARSER_H

#include <vector>
#include <cstdint>
#include <string>

class NumberParser{
    private:
        const char* filename;
        bool _is_number(const std::string &s);
    public:
        bool has_repeated_digits(const std::string &s);
        bool is_within_range(uint16_t number);
        NumberParser(const char* filename);
        ~NumberParser();
        std::vector<uint16_t> parse_numbers();
};

#endif