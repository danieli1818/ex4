//
// Created by daniel on 1/11/19.
//

#ifndef UNTITLED1_AIRDISTANCEHEURISTICFUNCTION_H
#define UNTITLED1_AIRDISTANCEHEURISTICFUNCTION_H

#include "HeuristicFunction.h"

class AirDistanceHeuristicFunction : public HeuristicFunction<pair<int, int>> {

public:

    virtual double operator()(State<pair<int, int>>& currentState, State<pair<int, int>>& goalState);

};


#endif //UNTITLED1_AIRDISTANCEHEURISTICFUNCTION_H
