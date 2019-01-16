//
// Created by daniel on 1/11/19.
//

#ifndef UNTITLED1_BREADTHFIRSTSEARCHSEARCHER_H
#define UNTITLED1_BREADTHFIRSTSEARCHSEARCHER_H

#include "Searcher.h"
#include "AStarSearcher.h"

template <class T>
class BreadthFirstSearchSearcher : public Searcher<T> {

    class HeuristicFunctionDefault;

    AStarSearcher<T> * m_searcher;
    HeuristicFunctionDefault * m_hfd;

    class HeuristicFunctionDefault : public HeuristicFunction<T> {

    public:

        virtual double operator()(State<T>& currentState, State<T>& goalState) {
            return 0;
        }

    };

public:

    BreadthFirstSearchSearcher() {
        m_hfd = new HeuristicFunctionDefault();
        m_searcher = new AStarSearcher<T>(m_hfd);
    }

    virtual list<T> search(Searchable<T> &searchable) {
        return m_searcher->search(searchable);
    }

    virtual ~BreadthFirstSearchSearcher() {
        delete m_hfd;
        delete m_searcher;
    }
};


#endif //UNTITLED1_BREADTHFIRSTSEARCHSEARCHER_H
