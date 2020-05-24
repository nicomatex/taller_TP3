#include <iomanip>
#include <iostream>

#include "client_config.h"
#include "client_game.h"
#include "common_network_error.h"

int main(int argc, char* argv[]) {
    if (argc != CLIENT_ARG_QTY) {
        std::cout << MSG_ERR_PARAMS << std::endl;
        return 0;
    }

    try {
        Game game(argv[ARG_POS_HOST], argv[ARG_POS_PORT]);
        game.run();
    } catch (NetworkError& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << MSG_ERR_UNKNOWN << std::endl;
    }
    return 0;
}
