#include <cstdint>
#include <iostream>

#include "server_game.h"

int main(void) {
    GameServer server("8080","eskere.txt");
    server.run();
    return 0;
}