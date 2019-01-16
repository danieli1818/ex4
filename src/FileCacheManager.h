//
// Created by daniel on 1/8/19.
//

#ifndef UNTITLED1_FILECACHEMANAGER_H
#define UNTITLED1_FILECACHEMANAGER_H

#include "CacheManager.h"

#include <map>
#include <string>
#include <fstream>
#include "Utils.h"

using std::map;
using std::string;
using std::fstream;
using std::ios;

namespace server_side {


    class FileCacheManager : public CacheManager {

        map<string, string> m_solutionsMap;
        fstream m_fileStream;
        string m_filename;
        string m_delimiter;

        void updateSolution(string problem, string solution);
        bool isEmpty(std::fstream& pFile);
        void reset();
        string transformListStringToString(list<string> strings);

    public:

        FileCacheManager(string filename, string delimiter);

        virtual bool exists(string problem);
        virtual bool listExists(list<string> problemList);
        virtual string getSolution(string problem);
        virtual string getListSolution(list<string> problemList);
        virtual void writeSolution(string problem, string solution);
        virtual void writeListSolution(list<string> problemList, string solution);


    };

}



#endif //UNTITLED1_FILECACHEMANAGER_H
