//
// Created by daniel on 1/13/19.
//

#ifndef UNTITLED1_SEARCHERSOLVER_H
#define UNTITLED1_SEARCHERSOLVER_H


#include "Solver.h"
#include "Searcher.h"

using namespace server_side;

template <class Problem, class Solution>
class SearcherSolver : public Solver<Problem, list<Solution>> {

    Searcher<Solution> * m_searcher;

public:

    SearcherSolver(Searcher<Solution> * searcher) {
        if (searcher == nullptr) {
            throw "Not Valid Searcher Pointer!!!!";
        }
        m_searcher = searcher;
    }

    list<Solution> solve(Problem problem) {
        return m_searcher->search(problem);
    }

};


#endif //UNTITLED1_SEARCHERSOLVER_H
