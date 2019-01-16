//
// Created by daniel on 1/10/19.
//

#ifndef UNTITLED1_ASTARSEARCHER_H
#define UNTITLED1_ASTARSEARCHER_H


#include "Searcher.h"
#include "HeuristicFunction.h"
#include "State.h"
#include <unordered_map>
#include <list>
#include <unordered_set>
#include <iostream>

template <class T>
class AStarSearcher : public Searcher<T> {

    HeuristicFunction<T> * m_hf;

    //class Node;

    State<T> getMinValueStateInList(list<State<T>> states) {
        State<T> minValueState;
        bool hasStarted = false;
        for (State<T> & state : states) {
            if (!hasStarted || minValueState.getCost() > state.getCost()) {
                minValueState = state;
            }
            hasStarted = true;
        }
        return minValueState;
    }

    list<T> constructPath(State<T> searchable) {
        list<T> path;
        State<T>* current = &searchable;
        while (current->getParent() != nullptr) {
            path.push_front(current->getValue());
            current = current->getParent();
        }
        path.push_front(current->getValue());
        return path;
    }

    bool listContainsState(list<State<T>> l, State<T> state) {
        for (State<T> & listState : l) {
            if (listState == (state)) {
                return true;
            }
        }
        return false;
    }

    bool unorderedSetContainsState(unordered_set<State<T>> uSet, State<T> state) {
        for (State<T> uSetState : uSet) {
            if (uSetState.equals(state)) {
                return true;
            }
        }
        return false;
    }

    State<T> getStateFromList(list<State<T>> l, State<T> state) {
        for (State<T> & listState : l) {
            if (listState == (state)) {
                return listState;
            }
        }
        throw "Error State Not Found!!!!";
    }

    State<T> getStateFromUnorderedSet(unordered_set<State<T>> uSet, State<T> state) {
        for (State<T> uSetState : uSet) {
            if (uSetState.equals(state)) {
                return uSetState;
            }
        }
        throw "Error State Not Found!!!!";
    }

    /*class Node {

        Searchable<T> m_value;
        Node * m_parent;
        double m_distance;

    public:

        Node(Searchable<T>& value, Node * parent, double distance) : m_value(value), m_parent(parent), m_distance(distance) {}

        Searchable<T> getValue() {
            return m_value;
        }

        Node * getParent() {
            return m_parent;
        }

        double getDistance() {
            return m_distance;
        }



    };*/

public:

    explicit AStarSearcher(HeuristicFunction<T>* hf) : m_hf(hf) {};

    virtual list<T> search(Searchable<T>& searchable) {
        int numOfNodesDeveloped = 0;
        list<State<T>> closeList;
        list<State<T>> openList;
        list<State<T>*> newList;
        State<T> initialState = searchable.getInitialState();
        State<T> goalState = searchable.getGoalState();
        initialState.setCost(m_hf->operator()(initialState, goalState));
        openList.push_back(initialState);
        while (!openList.empty()) {
            State<T> current = getMinValueStateInList(openList);
            numOfNodesDeveloped++;
            if (current == (goalState)) {
                list<T> path = constructPath(current);
                for (auto & element : newList) {
                    delete element;
                }
                return path;
            }
            openList.remove(current);
            closeList.push_back(current);
            list<State<T>> successors = searchable.getAllPossibleStates(current);
            for (State<T> & state : successors) {
                state.setCost(current.getCost() + state.getCost() + m_hf->operator()(state, goalState));
                State<T> * currentClone = new State<T>(current.getValue());
                currentClone->clone(current);
                newList.push_back(currentClone);
                state.setParent(currentClone);
                bool isInCloseList = listContainsState(closeList, state);
                bool isInOpenList = listContainsState(openList, state);
                if (!isInCloseList && !isInOpenList) {
                    openList.push_back(state);
                } else {
                    if (isInOpenList) {
                        State<T> st = getStateFromList(openList, state);
                        if (st.getCost() > state.getCost()) {
                            st.setCost(state.getCost());
                            st.setParent(currentClone);
                        }
                    } else {
                        State<T> st = getStateFromList(closeList, state);
                        if (st.getCost() > state.getCost()) {
                            st.setCost(state.getCost());
                            st.setParent(currentClone);
                        }
                    }
                }
            }
        }
        list<T> path;
        return path;
    }

};


#endif //UNTITLED1_ASTARSEARCHER_H
