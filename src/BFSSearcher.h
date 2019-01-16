//
// Created by daniel on 1/11/19.
//

#ifndef UNTITLED1_BFSSEARCHER_H
#define UNTITLED1_BFSSEARCHER_H

#include "Searcher.h"
#include <algorithm>
#include <queue>
#include <deque>
#include <iostream>

using namespace std;

template <class T>
class BFSSearcher : public Searcher<T> {

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
        list<State<T>> closeList;
        deque<State<T>> openList;
        list<State<T> *> pointersList;
        list<T> path;
        auto initialState = searchable.getInitialState();
        initialState.setCost(0);
        openList.push_back(initialState);
        while(!openList.empty()) {
            State<T> current = openList.front();
            numOfNodesDeveloped++;
            openList.pop_front();
            if (current == searchable.getGoalState()) {
                path = constructPath(current);
                break;
            }
            closeList.push_back(current);
            State<T> * currentPointer = new State<T>(current.getValue());
            currentPointer->clone(current);
            pointersList.push_back(currentPointer);
            list<State<T>> successors = searchable.getAllPossibleStates(current);
            for (State<T> & element : successors) {
                if (find(openList.begin(), openList.end(), element) != openList.end() || find(closeList.begin(), closeList.end(), element) != closeList.end()) {
                    continue;
                }
                element.setCost(current.getCost() + element.getCost());
                element.setParent(currentPointer);
                openList.push_back(element);
            }
        }
        for (State<T> * & element : pointersList) {
            delete element;
            element = nullptr;
        }
        return path;

    }

};


#endif //UNTITLED1_BFSSEARCHER_H
