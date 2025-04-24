#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <optional>

#include "adjacency_matrix.cpp"
#include "include/adjacency_matrix.hpp"
#include "adjacency_list.cpp"
#include "include/adjacency_list.hpp"

#include "dfs.cpp"
#include "include/dfs.hpp"


void test(int size, float density){
    float limit = size * (size - 1) * density / 2;

    AdjacencyMatrix graph(size);
    for (int edges = 0; edges < limit; edges++) {
            int u, v;
                do {
                    u = rand() % size;
                    v = rand() % size;
                } while (u == v);
            graph.addEdge(u, v, rand() % 10 + 1);
        }
    graph.print();
    graph.dumpToGraphviz();

    std::vector<bool> visited(size, false);
    dfs_matrix(graph, 0, visited, size);
}

void test2(int size, float density){
    float limit = size * (size - 1) * density / 2;

    AdjacencyList graph(size);
    for (int edges = 0; edges < limit; edges++) {
            int u, v;
                do {
                    u = rand() % size;
                    v = rand() % size;
                } while (u == v);
            graph.addEdge(u, v, rand() % 10 + 1);
        }
    graph.print();
    graph.dumpToGraphviz();

    std::vector<bool> visited(size, false);
    dfs_list(graph, 0, visited);
}



int main() {
    int SIZES[] = {10}; //50, 100, 200, 500
    float DENSITIES[] = {0.25}; //0.50, 0.75, 1.0
    
    for (int size : SIZES)
        for(float density : DENSITIES){
           // test(size, density);
           test2(size, density);
    }

    return 0;
}