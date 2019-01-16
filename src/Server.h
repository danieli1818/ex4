//
// Created by daniel on 1/8/19.
//

#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H

#include "ClientHandler.h"

namespace server_side {

    class Server {
    public:
        virtual void open(int port, ClientHandler& ch) = 0;
        virtual void stop() = 0;
    };

}

#endif //UNTITLED1_SERVER_H
