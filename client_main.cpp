#include <iomanip>
#include <iostream>
#include "client_game.h"
#include "common_error.h"
#include "client_config.h"

int main(int argc, char* argv[]) {

    try{
        Game game(argv[1],argv[2]);
        game.run();
    }catch(Error &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << MSG_ERR_UNKNOWN << std::endl;
    }
    return 0;
}