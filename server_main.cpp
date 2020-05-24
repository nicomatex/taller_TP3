#include <cstdint>
#include <iostream>

#include "server_config.h"
#include "server_game.h"

int main(int argc, char* argv[]) {
    if (argc != ARGS_QTY) {
        std::cerr << MSG_ERR_ARGS << std::endl;
        return 1;
    }

    GameServer server(argv[ARG_POS_PORT], argv[ARG_POS_NUMBERFILE]);
    server.run();
    return 0;
}
