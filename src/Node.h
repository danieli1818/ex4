//
// Created by daniel on 1/10/19.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

template <class T>
class Node {

    T m_value;
    Node<T> * m_parent;
    double m_distance;

public:

    Node(T& value, Node<T> * parent, double distance) : m_value(value), m_parent(parent), m_distance(distance) {}

    T getValue() {
        return m_value;
    }

    Node<T> * getParent() {
        return m_parent;
    }

    double getDistance() {
        return m_distance;
    }



};


#endif //UNTITLED1_NODE_H
