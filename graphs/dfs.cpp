#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <optional>

#include "include/dfs.hpp"

void dfs_matrix(const AdjacencyMatrix& graph, int start, std::vector<bool>& visited, int size) {
    visited[start] = true;
    std::cout << start << " ";

    Matrix matrix = graph.getMatrix();

    for (int i = 0; i < size; ++i) {
        if (matrix.get(start, i) != 0 && !visited[i]) {
            dfs_matrix(graph, i, visited, size);
        }
    }
}

void dfs_list(const AdjacencyList& graph, int start, std::vector<bool>& visited) {
    visited[start] = true;
    std::cout << start << " ";

    const std::vector<Edge>* adjacency = graph.getList();

    for (const Edge& edge : adjacency[start]) {
        if (!visited[edge.end]) {
            dfs_list(graph, edge.end, visited);
        }
    }
}