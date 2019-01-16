//
// Created by daniel on 1/13/19.
//

#include <netinet/in.h>
#include <unistd.h>
#include "MyParallelServer.h"

using namespace server_side;

MyParallelServer::MyParallelServer() : shouldStop(false) {}

void MyParallelServer::listen(void *port, server_side::ClientHandler &ch) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        delete static_cast<int *>(port);
        throw EXIT_FAILURE;
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        delete static_cast<int *>(port);
        throw EXIT_FAILURE;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    try {
        address.sin_port = htons(*static_cast<int *>(port) );
    } catch (...) {
        delete static_cast<int *>(port);
        throw "port not valid!!!!";
    }


    delete static_cast<int *>(port);

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        throw EXIT_FAILURE;
    }
    if (::listen(server_fd, NUM_OF_CLIENTS_PARALLEL_SERVER) < 0)
    {
        perror("listen");
        throw EXIT_FAILURE;
    }
    bool firstTime = true;
    while (!shouldStop) {
        if (!firstTime) {
            timeval timeout;
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
        }

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen))<0)
        {
            if (errno == EWOULDBLOCK) {
                stop();
                continue;
                //cout << "timeout!" << endl;
            }	else	{
                perror("other error");
                throw EXIT_FAILURE;
            }
        }
        handleClientParameters* hcp = new handleClientParameters{new_socket, ch};
        pthread_t t1;
        threads.push_back(t1);
        pthread_create(&threads.back(), nullptr, handleClient, hcp);
        firstTime = false;
    }
    for (pthread_t & thread : threads) {
        pthread_join(thread, nullptr);
    }
    close(server_fd);
}

void * MyParallelServer::handleClient(void *parameters) {
    handleClientParameters * socketPointer = static_cast<handleClientParameters *>(parameters);
    ClientHandler& ch = socketPointer->ch;
    int new_socket = socketPointer->new_socket;
    delete socketPointer;
    ch.handleClient(new_socket);
    return nullptr;
}

void MyParallelServer::open(int port, server_side::ClientHandler &ch) {
    int * portParameter = new int(port);
    listen(portParameter, ch);
}

void MyParallelServer::stop() {
    shouldStop = true;
}


