#include <iostream>

#include "client_parser.h"
#include "client_command_help.h"
#include "client_command_number.h"
#include "client_command_surrender.h"
#include "client_config.h"

ClientParser::ClientParser() {}

ClientParser::~ClientParser() {}

bool ClientParser::_is_number(const std::string& s) {
    for (size_t i = 0; i < s.length(); i++) {
        if (!std::isdigit(s[i])) return false;
    }
    return true;
}

Command* ClientParser::operator()() {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line == CMD_HELP) {
            return new CommandHelp();
        }
        if (line == CMD_SURRENDER) {
            return new CommandSurrender();
        }
        if (_is_number(line)) {
            return new CommandNumber((uint16_t)std::stoi(line));
        }
        std::cout << INVALID_CMD << std::endl;
    }
}
