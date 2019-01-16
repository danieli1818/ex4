//
// Created by daniel on 1/8/19.
//

#ifndef UNTITLED1_SOLVER_H
#define UNTITLED1_SOLVER_H

namespace server_side {

    template <class Problem, class Solution>
    class Solver {

    public:

        virtual Solution solve(Problem problem) = 0;
        virtual ~Solver() = default;

    };

}

#endif //UNTITLED1_SOLVER_H
