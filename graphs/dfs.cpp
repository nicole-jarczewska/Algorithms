#include "include/dfs.hpp"

std::vector<int> dfs_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag) {
    visited[start] = true;
    results.push_back(start);

    Matrix matrix = graph.getMatrix();

    for (int i = 0; i < size; ++i) {
        if (matrix.get(start, i) != 0 && !visited[i]) {
            dfs_matrix(graph, results, i, visited, size, testFlag);
        }
    }

    return results;
}

std::vector<int> dfs_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag) {
    visited[start] = true;
    results.push_back(start);

    Edge** adjacency = graph.getList();

    int edgeCount = graph.getSize(start);
    for (int i = 0; i < edgeCount; ++i) {
        const Edge& edge = adjacency[start][i];
        if (!visited[edge.end]) {
            dfs_list(graph, results, edge.end, visited, size, testFlag);
        }
    }

    return results;
}