//
// Created by daniel on 1/11/19.
//

#include "Matrix.h"

Matrix::Matrix(int **matrix, int rows, int columns) : m_rows(rows), m_columns(columns), m_initialStateI(0), m_initialStateJ(0), m_goalStateI(rows - 1), m_goalStateJ(columns - 1) {
    if (rows <= 0 || columns <= 0) {
        throw "Not Valid Matrix!!!!";
    }
    for (int i = 0; i < rows; ++i) {
        vector<State<pair<int, int>>> currentRow;
        m_matrix.push_back(currentRow);
        for (int j = 0; j < columns; ++j) {
            State<pair<int, int>> state = State<pair<int, int>>(pair<int, int>(i, j));
            state.setCost(matrix[i][j]);
            m_matrix[i].push_back(state);
        }
    }
}

Matrix::Matrix(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        throw "Not Valid Matrix!!!!";
    }
    m_rows = (int)matrix.size();
    m_columns = (int)matrix[0].size();
    if (m_rows <= 0 || m_columns <= 0) {
        throw "Big Matrix!!!!";
    }
    for (int i = 0; i < m_rows; ++i) {
        vector<State<pair<int, int>>> currentRow;
        if (matrix[i].size() != (unsigned int)m_columns) {
            throw "Not Valid Matrix!!!!";
        }
        m_matrix.push_back(currentRow);
        for (int j = 0; j < m_columns; ++j) {
            State<pair<int, int>> state = State<pair<int, int>>(pair<int, int>(i, j));
            state.setCost(matrix[i][j]);
            m_matrix[i].push_back(state);
        }
    }
    m_initialStateI = 0;
    m_initialStateJ = 0;
    m_goalStateI = (m_rows - 1);
    m_goalStateJ = (m_columns - 1);
}

State<pair<int, int>> Matrix::getInitialState() {
    return m_matrix[m_initialStateI][m_initialStateJ];
}

State<pair<int, int>> Matrix::getGoalState() {
    return m_matrix[m_goalStateI][m_goalStateJ];
}

list<State<pair<int, int>>> Matrix::getAllPossibleStates(State<pair<int, int>> s) {
    pair<int, int> value = s.getValue();
    if (!isValidState(value.first, value.second)) {
        throw "State Not In Matrix!!!!";
    }
    int i = value.first;
    int j = value.second;
    list<State<pair<int, int>>> possibleStatesList;
    bool shouldAdd = false;
    for (int k = i - 1; k <= i + 1; ++k) {
        for (int l = j - 1; l <= j + 1 ; ++l) {
            if (!shouldAdd || !isValidState(k , l)|| m_matrix[k][l].getCost() == -1) {
                shouldAdd = !shouldAdd;
                continue;
            }
            possibleStatesList.push_back(m_matrix[k][l]);
            shouldAdd = !shouldAdd;
        }
    }
    return possibleStatesList;
}

inline bool Matrix::isValidState(int i, int j) {
    return !(i < 0 || i >= m_rows || j < 0 || j >= m_columns);
}

void Matrix::setInitialState(int i, int j) {
    if (!isValidState(i, j)) {
        throw "Not Valid State!!!!";
    }
    m_initialStateI = i;
    m_initialStateJ = j;
}

void Matrix::setGoalState(int i, int j) {
    if (!isValidState(i, j)) {
        throw "Not Valid State!!!!";
    }
    m_goalStateI = i;
    m_goalStateJ = j;
}

list<string> Matrix::toString() {
    list<string> resultList;
    resultList.push_back(to_string(m_rows));
    resultList.push_back(to_string(m_columns));
    resultList.push_back(to_string(m_initialStateI) + "," + to_string(m_initialStateJ));
    resultList.push_back(to_string(m_goalStateI) + "," + to_string(m_goalStateJ));
    for (int i = 0; i < m_rows; ++i) {
        string row;
        for (int j = 0; j < m_columns - 1; ++j) {
            row += to_string(m_matrix[i][j].getCost()) + ",";
        }
        row += to_string(m_matrix[i][m_columns - 1].getCost());
        resultList.push_back(row);
    }
    return resultList;
}

void Matrix::fromString(list<string> &strings, list<string>::iterator &it) {
    if (it == strings.end()) {
        throw "Not Valid strings!!!!";
    }
    m_rows = stoi(*it);
    it++;
    if (it == strings.end()) {
        throw "Not Valid strings!!!!";
    }
    m_columns = stoi(*it);
    it++;
    if (it == strings.end()) {
        throw "Not Valid strings!!!!";
    }
    string line = *it;
    vector<string> splittedLine = Utils::split(line, ",");
    if (splittedLine.size() != 2) {
        throw "Not Valid strings!!!!";
    }
    m_initialStateI = stoi(splittedLine[0]);
    m_initialStateJ = stoi(splittedLine[1]);
    it++;
    if (splittedLine.size() != 2) {
        throw "Not Valid strings!!!!";
    }
    line = *it;
    splittedLine = Utils::split(line, ",");
    if (splittedLine.size() != 2) {
        throw "Not Valid strings!!!!";
    }
    m_goalStateI = stoi(splittedLine[0]);
    m_goalStateJ = stoi(splittedLine[1]);
    it++;
    m_matrix.clear();
    for (int i = 0; i < m_rows; ++i) {
        line = *it;
        splittedLine = Utils::split(line, ",");
        if (splittedLine.size() != (unsigned int)m_columns) {
            throw "Not Valid strings!!!!";
        }
        vector<State<pair<int, int>>> row;
        for (int j = 0; j < m_columns; ++j) {
            row.emplace_back(State<pair<int, int>>(pair<int, int>(i, j)));
        }
        m_matrix.push_back(row);
        it++;
    }
}

double Matrix::getCostOfPath(list<pair<int, int>> path) {
    double cost = 0;
    bool firstTime = true;
    for (auto const& cell : path) {
        if (firstTime) {
            firstTime = false;
            continue;
        }
        cost += m_matrix[cell.first][cell.second].getCost();
    }
    return cost;
}




