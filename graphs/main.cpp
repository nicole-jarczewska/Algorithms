#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <optional>

#include "adjacency_matrix.cpp"
#include "adjacency_matrix.hpp"
#include "adjacency_list.cpp"
#include "adjacency_list.hpp"



int main() {
    int SIZES[] = {10, 50, 100, 200, 500};

    AdjacencyMatrix graph(4);
    graph.addEdge(0, 1, 3);
    graph.addEdge(1, 2, 4);
    graph.addEdge(2, 3, 5);
    graph.print();

    graph.removeEdge(1, 2);
    graph.print();

    return 0;
}