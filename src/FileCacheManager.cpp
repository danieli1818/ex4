//
// Created by daniel on 1/8/19.
//

#include <iostream>
#include "FileCacheManager.h"

using namespace server_side;

FileCacheManager::FileCacheManager(string filename, string delimiter) {
    m_filename = filename;
    m_delimiter = delimiter;
    m_fileStream.open(filename, ios::out | ios::in);
    if (m_fileStream.fail()) {
        m_fileStream.close();
        m_fileStream.open(filename, ios::out);
        if (m_fileStream.fail()) {
            throw "Could Not Open File : " + filename;
        }
        m_fileStream.close();
        m_fileStream.open(filename, ios::out | ios::in);
        if (m_fileStream.fail()) {
            throw "Could Not Open File : " + filename;
        }
    }
    if (!isEmpty(m_fileStream)) {
        string line;
        while (std::getline(m_fileStream, line)) {
            vector<string> splitted = Utils::split(line, delimiter);
            if (line.empty() || splitted.empty()) {
                continue;
            }
            if (splitted.size() == 1) {
                m_solutionsMap[""] = splitted[0];
                continue;
            }
            if (splitted.size() == 2) {
                m_solutionsMap[splitted[0]] = splitted[1];
                continue;
            }
            string key;
            for (unsigned int i = 0; i < splitted.size() - 2; ++i) {
                key += splitted[i] + "$";
            }
            key += splitted[splitted.size() - 2];
            m_solutionsMap[key] = splitted[splitted.size() - 1];
        }
    }
    if (m_fileStream.is_open()) {
        m_fileStream.seekg(0, ios_base::beg);
    } else {
        throw "Error Opening The File!!!!";
    }
    //m_fileStream << "yay" << endl;
    reset();


}

bool FileCacheManager::isEmpty(std::fstream &pFile) {
    pFile.seekg(0, ios_base::beg);
    return pFile.peek() == std::fstream::traits_type::eof();
}

bool FileCacheManager::exists(string problem) {
    return (bool)m_solutionsMap.count(problem);
}

bool FileCacheManager::listExists(list<string> problemList) {
    string problemListStr = transformListStringToString(problemList);
    return exists(problemListStr);
}

string FileCacheManager::getSolution(string problem) {
    if (exists(problem)) {
        return m_solutionsMap[problem];
    }
    throw "Solution doesn't exist in cache!!!!";
}

string FileCacheManager::getListSolution(list<string> problemList) {
    string problemListStr = transformListStringToString(problemList);
    return getSolution(problemListStr);
}

void FileCacheManager::writeSolution(string problem, string solution) {
    reset();
    if (exists(problem)) {
        updateSolution(problem, solution);
    } else {
        reset();
        m_fileStream.seekg(0, ios_base::end);
        m_fileStream << problem;
        m_fileStream << m_delimiter;
        m_fileStream << solution;
        m_fileStream << endl;
        m_solutionsMap[problem] = solution;
        reset();
        //m_fileStream.close();
        //m_fileStream.open("test.txt", ios::out | ios::in);
    }
}

void FileCacheManager::writeListSolution(list<string> problemList, string solution) {
    string problemListStr = transformListStringToString(problemList);
    writeSolution(problemListStr, solution);
}

void FileCacheManager::updateSolution(string problem, string solution) {
    m_fileStream.seekp(ios_base::beg);
    string line;
    unsigned long prev = m_fileStream.cur;
    bool found = false;
    while (std::getline(m_fileStream, line)) {
        vector<string> splitted = Utils::split(line, m_delimiter);
        if (splitted.size() != 2) {
            throw "Not Valid Line : " + line + " !!!!";
        }
        if (splitted[0] == problem) {
            found = true;
            break;
        }
    }
    if (found) { //TODO check if all line was deleted rewrite all to a new file
        m_fileStream.seekp(prev);
        m_fileStream.write(problem.c_str(), problem.length());
        m_fileStream.write(m_delimiter.c_str(), m_delimiter.length());
        m_fileStream.write(solution.c_str(), solution.length());
        m_fileStream.write("\n", 1);
        m_solutionsMap[problem] = solution;
    }
    throw "Not Found Update Exception!!!!";
}

void FileCacheManager::reset() {
    m_fileStream.close();
    m_fileStream.open(m_filename, ios::out | ios::in);
    m_fileStream.seekg(0, ios_base::beg);
}

string FileCacheManager::transformListStringToString(list<string> strings) {
    if (strings.empty()) {
        throw "Error";
    }
    if (strings.size() == 1) {
        return *strings.begin();
    }
    string problemListStr;
    list<string>::iterator it = strings.begin();
    for (unsigned int i = 0; i < strings.size() - 1; ++i) {
        problemListStr += *it + m_delimiter;
        it++;
    }
    problemListStr += *it;
    return problemListStr;
}


