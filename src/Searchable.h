//
// Created by daniel on 1/10/19.
//

#ifndef UNTITLED1_SEARCHABLE_H
#define UNTITLED1_SEARCHABLE_H

#include "State.h"
#include <list>
#include <map>

using namespace std;

template <class T>
class Searchable {

public:

    virtual State<T> getInitialState() = 0;
    virtual State<T> getGoalState() = 0;
    virtual list<State<T>> getAllPossibleStates(State<T> s) = 0;


    //virtual map<T, double> getChildrenStates() = 0; // map of children states of weights and child.

    //virtual T getValue() = 0;

    virtual ~Searchable() = default;

};

#endif //UNTITLED1_SEARCHABLE_H
