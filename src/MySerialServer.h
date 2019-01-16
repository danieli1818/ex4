//
// Created by daniel on 1/8/19.
//

#ifndef UNTITLED1_MYSERIALSERVER_H
#define UNTITLED1_MYSERIALSERVER_H

#include "Server.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <strings.h>
#include "ClientHandler.h"

#define NUM_OF_CLIENTS_SERIAL_SERVER 1

namespace server_side {

    class MySerialServer : public Server {

        bool shouldStop;

        void listen(void * port, ClientHandler& ch);

    public:

        MySerialServer();

        virtual void open(int port, ClientHandler& ch);

        virtual void stop();

};

}


#endif //UNTITLED1_MYSERIALSERVER_H
