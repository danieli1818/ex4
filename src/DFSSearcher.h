//
// Created by daniel on 1/12/19.
//

#ifndef UNTITLED1_DFSSEARCHER_H
#define UNTITLED1_DFSSEARCHER_H

#include "Searcher.h"
#include <algorithm>
#include <deque>
#include <iostream>

template <class T>
class DFSSearcher : public Searcher<T> {

    list<T> constructPath(State<T> state) {
        list<T> path;
        State<T> * current = &state;
        while (current->getParent() != nullptr) {
            path.push_front(current->getValue());
            current = current->getParent();
        }
        path.push_front(current->getValue());
        return path;
    }

public:

    virtual list<T> search(Searchable<T>& searchable) {

        int numOfNodesDeveloped = 0;
        deque<State<T>> openList;
        list<State<T>> closeList;
        list<State<T>*> pointersList;
        list<T> path;
        auto initialState = searchable.getInitialState();
        initialState.setCost(0);
        openList.push_front(initialState);
        while (!openList.empty()) {
            State<T> currentState = openList.front();
            numOfNodesDeveloped++;
            openList.pop_front();
            if (currentState == searchable.getGoalState()) {
                path = constructPath(currentState);
                break;
            }
            closeList.push_back(currentState);
            State<T> * currentStatePointer = new State<T>(currentState.getValue());
            currentStatePointer->clone(currentState);
            pointersList.push_back(currentStatePointer);
            list<State<T>> successors = searchable.getAllPossibleStates(currentState);
            for (State<T> & element : successors) {
                if (find(openList.begin(), openList.end(), element) != openList.end() || find(closeList.begin(), closeList.end(), element) != closeList.end()) {
                    continue;
                }
                element.setCost(element.getCost() + currentState.getCost());
                element.setParent(currentStatePointer);
                openList.push_front(element);
            }
        }
        for (State<T> * & element : pointersList) {
            delete element;
            element = nullptr;
        }
        return path;



    }



};


#endif //UNTITLED1_DFSSEARCHER_H
