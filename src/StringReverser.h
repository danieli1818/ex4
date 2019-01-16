//
// Created by daniel on 1/9/19.
//

#ifndef UNTITLED1_STRINGREVERSER_H
#define UNTITLED1_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <sstream>

using namespace server_side;

using std::string;
using std::stringstream;

namespace server_side {
    class StringReverser : public Solver<string, string> {

    public:

        StringReverser() = default;

        virtual string solve(string str);

    };
}


#endif //UNTITLED1_STRINGREVERSER_H
