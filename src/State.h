//
// Created by daniel on 1/11/19.
//

#ifndef UNTITLED1_STATE_H
#define UNTITLED1_STATE_H

template <class T>
class State {

    T m_state;    // the state
    double m_cost;     // cost to reach this state (set by a setter)
    State<T> * m_cameFrom;  // the state we came from to this state (setter)

public:

    State<T>() = default;

    explicit State<T>(T state) {
        m_state = state;
        m_cost = 0;
        m_cameFrom = nullptr;
    }    // CTOR { this.state = state; }

    void clone(State<T>& state) {
        m_state = (state.getValue());
        m_cost = state.getCost();
        m_cameFrom = state.getParent();
    }

    bool operator==(State<T> s) {
        return m_state == (s.m_state);
    }    // we overload Object's Equals method { return state.Equals(s.state); }

    T getValue() {
        return m_state;
    }

    double getCost() {
        return m_cost;
    }

    State<T> * getParent() {
        return m_cameFrom;
    }

    void setValue(T state) {
        m_state = state;
    }

    void setCost(double cost) {
        m_cost = cost;
    }

    void setParent(State<T> * parent) {
        m_cameFrom = parent;
    }

};


#endif //UNTITLED1_STATE_H
