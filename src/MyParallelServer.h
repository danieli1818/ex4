//
// Created by daniel on 1/13/19.
//

#ifndef UNTITLED1_MYPARALLELSERVER_H
#define UNTITLED1_MYPARALLELSERVER_H

#include "ClientHandler.h"
#include <pthread.h>
#include <list>

#define NUM_OF_CLIENTS_PARALLEL_SERVER 1000

namespace server_side {

    using namespace std;

    class MyParallelServer {

        bool shouldStop;
        list<pthread_t> threads;

        void listen(void * port, ClientHandler& ch);
        static void * handleClient(void * parameters);

    public:

        MyParallelServer();

        virtual void open(int port, ClientHandler& ch);

        virtual void stop();

    };

    struct handleClientParameters {
        int new_socket;
        ClientHandler& ch;
    };

}


#endif //UNTITLED1_MYPARALLELSERVER_H
