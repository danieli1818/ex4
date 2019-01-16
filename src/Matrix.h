//
// Created by daniel on 1/11/19.
//

#ifndef UNTITLED1_MATRIX_H
#define UNTITLED1_MATRIX_H

#include <vector>
#include <list>
#include <string>

#include "Searchable.h"
#include "State.h"
#include "Utils.h"

class Matrix : public Searchable<pair<int, int>> {

    vector<vector<State<pair<int, int>>>> m_matrix;
    int m_rows;
    int m_columns;
    int m_initialStateI;
    int m_initialStateJ;
    int m_goalStateI;
    int m_goalStateJ;

    bool isValidState(int i, int j);

public:

    Matrix(int** matrix, int rows, int columns);
    explicit Matrix(vector<vector<int>>& matrix);

    virtual State<pair<int, int>> getInitialState();

    virtual State<pair<int, int>> getGoalState();

    virtual list<State<pair<int, int>>> getAllPossibleStates(State<pair<int, int>> s);

    void setInitialState(int i, int j);

    void setGoalState(int i, int j);

    list<string> toString();

    void fromString(list<string>& strings, list<string>::iterator& it);

    double getCostOfPath(list<pair<int, int>> path);






};


#endif //UNTITLED1_MATRIX_H
