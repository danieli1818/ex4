//
// Created by daniel on 1/11/19.
//

#include "AirDistanceHeuristicFunction.h"
#include <math.h>

double AirDistanceHeuristicFunction::operator()(State<pair<int, int>>& currentState, State<pair<int, int>>& goalState) {
    double deltaI = goalState.getValue().first - currentState.getValue().first;
    double deltaJ = goalState.getValue().second - currentState.getValue().second;
    return sqrt(deltaI * deltaI + deltaJ * deltaJ);
}


