//
// Created by daniel on 1/10/19.
//

#ifndef UNTITLED1_HEURISTICFUNCTION_H
#define UNTITLED1_HEURISTICFUNCTION_H

#include "Searchable.h"

template <class T>
class HeuristicFunction {

public:

    virtual double operator()(State<T>& currentState, State<T>& goalState) = 0;
    virtual ~HeuristicFunction() {};

};


#endif //UNTITLED1_HEURISTICFUNCTION_H
