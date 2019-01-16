//
// Created by daniel on 1/12/19.
//

#ifndef UNTITLED1_MYCLIENTHANDLER_H
#define UNTITLED1_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Utils.h"
#include "Matrix.h"
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <vector>

#define BUFFER_LENGTH_MY_CLIENT_HANDLER 10000

using namespace server_side;

class MyClientHandler : public ClientHandler {

    Solver<Matrix, list<pair<int, int>>> * m_solver;
    CacheManager * m_cm;

public:

    MyClientHandler(Solver<Matrix, list<pair<int, int>>> *  solver, CacheManager * cm);

    virtual void handleClient(int sock);


};


#endif //UNTITLED1_MYCLIENTHANDLER_H
