#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "Main1.h"
#include "Searcher.h"
#include "AStarSearcher.h"
#include "Matrix.h"
#include "AirDistanceHeuristicFunction.h"
#include "BreadthFirstSearchSearcher.h"
#include "BFSSearcher.h"
#include "DFSSearcher.h"
#include "MyParallelServer.h"
#include "MyClientHandler.h"
#include "SearcherSolver.h"

using namespace server_side::boot;

int main(int args, char** argv) {
    if (args != 2) {
        throw "Not Valid Main Arguments!!!!";
    }
    int port;
    try {
        port = stoi(argv[1]);
    } catch (...) {
        throw "Not Valid Main Arguments!!!!";
    }
    MyParallelServer server;
    auto* hf = new AirDistanceHeuristicFunction();
    Searcher<pair<int, int>> * searcher = new DFSSearcher<pair<int, int>>();
    Solver<Matrix, list<pair<int, int>>> * solver = new SearcherSolver<Matrix, pair<int, int>>(searcher);
    FileCacheManager * cache = new FileCacheManager("test.txt", "$");
    auto ClientHandler = MyClientHandler(solver, cache);
    server.open(port, ClientHandler);
    delete hf;
    delete searcher;
    delete solver;
    delete cache;
    return 0;
    /*
    //Main::main(args, argv);
    //MyParallelServer server;
    //server.open()
    auto* hf = new AirDistanceHeuristicFunction();
    //DFSSearcher<pair<int, int>> searcher = DFSSearcher<pair<int, int>>();
    //BFSSearcher<pair<int, int>> searcher = BFSSearcher<pair<int, int>>();
    //BreadthFirstSearchSearcher<pair<int, int>> searcher = BreadthFirstSearchSearcher<pair<int, int>>();
    AStarSearcher<pair<int, int>> searcher = AStarSearcher<pair<int, int>>(hf);
    int* array = new int[4];
    array[0] = 1;
    array[1] = 1;
    array[2] = 1;
    array[3] = 1;
    int** matrix = new int*[4];
    matrix[0] = array;
    matrix[1] = array;
    matrix[2] = array;
    matrix[3] = array;
    Matrix m = Matrix(matrix, 4, 4);
    list<pair<int, int>> l = searcher.search(m);
    delete[] matrix;
    delete[] array;
    delete hf;*/
    /*fstream file;
    //file.open("test.txt", ios::out);
    //file.close();
    file.open("test.txt", ios::in | ios::out);
    file.seekg(0, ios_base::end);
    file << "hi" << endl;
    file.close();*/
}





