//
// Created by daniel on 1/12/19.
//

#include "MyClientHandler.h"

using namespace std;

MyClientHandler::MyClientHandler(Solver<Matrix, list<pair<int, int>>> * solver, CacheManager * cm) : m_solver(solver), m_cm(cm) {}

void MyClientHandler::handleClient(int sock) {

    ssize_t valread;
    char buffer[BUFFER_LENGTH_MY_CLIENT_HANDLER] = {0};
    std::string bufferStr;
    vector<string> lines;
    do {
        while (bufferStr.find('\n') == std::string::npos) {
            bzero(buffer, BUFFER_LENGTH_MY_CLIENT_HANDLER);
            valread = read( sock , buffer, BUFFER_LENGTH_MY_CLIENT_HANDLER);
            if (valread == 0) {
                std::cerr << "Unexpected Close!!!!" << std::endl; //TODO fix
                close(sock);
                return;
            }
            bufferStr += buffer;
        }
        string left = bufferStr.substr(bufferStr.find('\n') + 1, bufferStr.length());
        bufferStr = bufferStr.substr(0, bufferStr.find('\n'));
        if (bufferStr == "end") {
            break;
        }
        lines.push_back(bufferStr);
        bufferStr = left;
    } while (bufferStr != "end");
    unsigned long length = lines.size();
    if (length <= 2) {
        throw "Matrix is not Valid!!!";
    }
    vector<vector<int>> matrix;
    for (unsigned int i = 0; i < length - 2; ++i) {
        string line = lines[i];
        vector<string> splittedLine = Utils::split(line, ",");
        for (unsigned int k = 0; k < splittedLine.size(); ++k) {
            splittedLine[k] = Utils::trim(splittedLine[k]);
        }
        vector<int> row;
        unsigned long columns = splittedLine.size();
        for (unsigned int j = 0; j < columns; ++j) {
            row.push_back(stoi(splittedLine[j]));
        }
        row.shrink_to_fit();
        matrix.push_back(row);
    }
    Matrix mMatrix(matrix);
    string line = lines[length - 2];
    vector<string> splittedLine = Utils::split(line, ",");
    if (splittedLine.size() != 2) {
        throw "Not Valid Line!!!!";
    }
    mMatrix.setInitialState(stoi(splittedLine[0]), stoi(splittedLine[1]));
    line = lines[length - 1];
    splittedLine = Utils::split(line, ",");
    if (splittedLine.size() != 2) {
        throw "Not Valid Line!!!!";
    }
    mMatrix.setGoalState(stoi(splittedLine[0]), stoi(splittedLine[1]));
    list<string> matrixStr = mMatrix.toString();
    if (m_cm->listExists(matrixStr)) {
        std::string solution = m_cm->getListSolution(matrixStr);
        solution += "\n";
        send( sock, solution.c_str(), solution.length(), 0);
    } else {
        list<pair<int, int>> path = m_solver->solve(mMatrix);
        string solution;
        list<pair<int, int>>::iterator it = path.begin();
        for (unsigned int i = 0; i < path.size() - 2; ++i) {
            pair<int, int> current = *it;
            pair<int, int> next = *(++it);
            if (current.second < next.second) {
                solution += "Right,";
            } else if (current.second > next.second) {
                solution += "Left,";
            } else if (current.first < next.first) {
                solution += "Down,";
            } else {
                solution += "Up,";
            }
        }
        pair<int, int> current = *it;
        pair<int, int> next = *(++it);
        if (current.second < next.second) {
            solution += "Right";
        } else if (current.second > next.second) {
            solution += "Left";
        } else if (current.first < next.first) {
            solution += "Down";
        } else {
            solution += "Up";
        }
        m_cm->writeListSolution(matrixStr, solution);
        solution += "\n";
        send( sock, solution.c_str(), solution.length(), 0);
    }
    close(sock);

}


