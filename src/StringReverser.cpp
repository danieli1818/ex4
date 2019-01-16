//
// Created by daniel on 1/9/19.
//

#include "StringReverser.h"

string StringReverser::solve(string str) {
    stringstream ss;

    if (str.empty()) {
        return str;
    }

    for (unsigned long i = str.length() - 1; i > 0 ; --i) {
        ss << str[i];
    }
    ss << str[0];

    return ss.str();
}


