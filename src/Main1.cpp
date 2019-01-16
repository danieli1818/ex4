//
// Created by daniel on 1/10/19.
//

#include "Main1.h"

using namespace server_side::boot;

int Main::main(int args, char **argv) {
    if (args != 2) {
        throw "Not Valid Main Arguments!!!!";
    }
    int port;
    try {
        port = stoi(argv[1]);
    } catch (...) {
        throw "Not Valid Main Arguments!!!!";
    }
    MySerialServer server;
    Solver<std::string, std::string> * solver = new StringReverser();
    FileCacheManager * cache = new FileCacheManager("test.txt", "$");
    auto testClientHandler = MyTestClientHandler(solver, cache);
    server.open(port, testClientHandler);
    delete solver;
    delete cache;
    return 0;
}




