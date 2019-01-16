cmake_minimum_required(VERSION 3.13)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(untitled1 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.cpp FileCacheManager.h StringReverser.cpp StringReverser.h Utils.cpp Utils.h Main1.cpp Main1.h Searchable.h Searcher.h AStarSearcher.cpp AStarSearcher.h HeuristicFunction.h Node.cpp Node.h State.cpp State.h Matrix.cpp Matrix.h AirDistanceHeuristicFunction.cpp AirDistanceHeuristicFunction.h Pair.cpp Pair.h BreadthFirstSearchSearcher.cpp BreadthFirstSearchSearcher.h BFSSearcher.cpp BFSSearcher.h DFSSearcher.cpp DFSSearcher.h MyClientHandler.cpp MyClientHandler.h SearcherSolver.cpp SearcherSolver.h MyParallelServer.cpp MyParallelServer.h)