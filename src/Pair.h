//
// Created by daniel on 1/11/19.
//

#ifndef UNTITLED1_PAIR_H
#define UNTITLED1_PAIR_H

#include <map>

using namespace std;

template<class T1, class T2>
class Pair {

    pair<T1, T2> m_value;

public:

    Pair<T1, T2>(T1 value1, T2 value2) {
        m_value = pair<T1, T2>(value1, value2);
    }

    T1 getFirst() {
        return m_value.first;
    }

    T2 getSecond() {
        return m_value.second;
    }

    bool equals(Pair<T1, T2>& otherPair) {
        return (getFirst() == otherPair.getFirst() && getSecond() == otherPair.getSecond());
    }

};


#endif //UNTITLED1_PAIR_H
