//
// Created by daniel on 1/8/19.
//

#ifndef UNTITLED1_CLIENTHANDLER_H
#define UNTITLED1_CLIENTHANDLER_H

#include <iostream>

namespace server_side {

    class ClientHandler {
    public:
        virtual void handleClient(int sock) = 0;
    };

}

#endif //UNTITLED1_CLIENTHANDLER_H
