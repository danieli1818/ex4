//
// Created by daniel on 1/8/19.
//

#ifndef UNTITLED1_MYTESTCLIENTHANDLER_H
#define UNTITLED1_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <string>

#define BUFFER_LENGTH 1024



namespace server_side {
    class MyTestClientHandler : public ClientHandler {
        Solver<std::string, std::string> * m_solver;
        CacheManager * m_cm;

        //void start();

    public:

        MyTestClientHandler(Solver<std::string, std::string>* solver, CacheManager* cm);
        virtual void handleClient(int sock);

    };
}


#endif //UNTITLED1_MYTESTCLIENTHANDLER_H
