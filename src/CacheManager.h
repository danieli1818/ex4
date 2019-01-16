//
// Created by daniel on 1/8/19.
//

#ifndef UNTITLED1_CACHEMANAGER_H
#define UNTITLED1_CACHEMANAGER_H

#include <string>
#include <list>

using namespace std;

namespace server_side {

    class CacheManager {
    public:
        virtual bool exists(std::string problem) = 0;
        virtual bool listExists(list<string> problemList) = 0;
        virtual std::string getSolution(std::string problem) = 0;
        virtual std::string getListSolution(list<string> problemList) = 0;
        virtual void writeSolution(std::string problem, std::string solution) = 0;
        virtual void writeListSolution(list<string> problemList, std::string solution) = 0;
        virtual ~CacheManager() {};
    };

}

#endif //UNTITLED1_CACHEMANAGER_H
