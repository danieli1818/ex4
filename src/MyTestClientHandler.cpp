//
// Created by daniel on 1/8/19.
//

#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <sstream>
#include "MyTestClientHandler.h"

using namespace server_side;

MyTestClientHandler::MyTestClientHandler(server_side::Solver<std::string, std::string> *solver,
                                         server_side::CacheManager *cm)
                                         : m_solver(solver), m_cm(cm){

}

void MyTestClientHandler::handleClient(int sock) {
    ssize_t valread;
    char buffer[BUFFER_LENGTH] = {0};
    std::string bufferStr;
    do {
        bufferStr.clear();
        while (bufferStr.find('\n') == std::string::npos) {
            bzero(buffer, BUFFER_LENGTH);
            valread = read( sock , buffer, BUFFER_LENGTH);
            if (valread == 0) {
                std::cerr << "Unexpected Close!!!!" << std::endl;
                close(sock);
                return;
            }
            bufferStr += buffer;
        }
        bufferStr = bufferStr.substr(0, bufferStr.find('\n'));
        if (bufferStr == "end") {
            break;
        }
        if (m_cm->exists(bufferStr)) {
            std::string solution = m_cm->getSolution(bufferStr);
            //solution += "\n";
            send( sock, solution.c_str(), solution.length(), 0);
        } else {
            std::string solution = m_solver->solve(bufferStr);
            m_cm->writeSolution(bufferStr, solution);
            //solution += "\n";
            send( sock, solution.c_str(), solution.length(), 0);
        }
        fsync(sock);
    } while (bufferStr != "end");
    close(sock);
}
//
//void MyTestClientHandler::start() {
//    ssize_t valread;
//    char buffer[BUFFER_LENGTH] = {0};
//    valread = read( m_sock , buffer, BUFFER_LENGTH);
//    std::string bufferStr;
//    bool isFirstTime = true;
//    std::stringstream iss;
//    std::stringstream oss;
//    do {
//        /*while (bufferStr.find('\n') != std::string::npos) {
//            bzero(buffer, BUFFER_LENGTH);
//            valread = read(m_sock, buffer, BUFFER_LENGTH);
//            bufferStr += buffer;
//        }*/
//        if (!isFirstTime) {
//            iss << bufferStr;
//            bufferStr = buffer;
//            while (bufferStr.find('\n') != std::string::npos) {
//                while (valread > 0) {
//                    bzero(buffer, BUFFER_LENGTH);
//                    valread = read( m_sock , buffer, BUFFER_LENGTH);
//                    bufferStr += buffer;
//                }
//            }
//            bufferStr = bufferStr.substr(0, bufferStr.find('\n'));
//            std::stringstream ss;
//            ss << bufferStr;
//            handleClient()
//            /*int i = 0;
//            for (i = 0; i < BUFFER_LENGTH; ++i) {
//                if (buffer[i] == '\n') {
//                    i++;
//                    break;
//                }
//            }
//            int j = i;
//            for (; i < valread; ++i) {
//                buffer[i - j] = buffer[i];
//            }
//            if (i < BUFFER_LENGTH) {
//                buffer[i] = 0;
//            }*/
//        }
//        isFirstTime = false;
//    } while (bufferStr != "end");
//    handleClient(iss, oss);
//    close(m_sock);
    //printf("%s\n",buffer );
    //send(new_socket , hello , strlen(hello) , 0 );
    //printf("Hello message sent\n");
//}


