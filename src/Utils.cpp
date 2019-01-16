//
// Created by daniel on 1/9/19.
//

#include "Utils.h"

vector<string> Utils::split(string str, const string &delimiter) {
    vector<string> result;
    unsigned long i;
    while ((i = str.find(delimiter)) != string::npos) {
        result.push_back(str.substr(0, i));
        str = str.substr(i + 1, string::npos);
    }
    if (!str.empty()) {
        result.push_back(str);
    }
    return result;
}


