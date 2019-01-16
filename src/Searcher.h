//
// Created by daniel on 1/10/19.
//

#ifndef UNTITLED1_SEARCHER_H
#define UNTITLED1_SEARCHER_H

#include "Searchable.h"
#include <list>

template <class T>
class Searcher {

protected:

public:

    virtual list<T> search(Searchable<T>& searchable) = 0;

    virtual ~Searcher() = default;

};

#endif //UNTITLED1_SEARCHER_H
