#include "include/bellman_ford.hpp"

std::vector<int> bellman_ford_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size) {
    int max = 2147483647;
    std::vector<int> shortest_path(size, max);
    shortest_path[start] = 0;

    Matrix matrix = graph.getMatrix();

    for (int i = 1; i <= size - 1; i++) {
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                int weight = matrix.get(u, v);
                if (weight != 0 && weight != max && shortest_path[u] != max && shortest_path[u] + weight < shortest_path[v]) {
                    shortest_path[v] = shortest_path[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            int weight = matrix.get(u, v);
            if (weight != 0 && weight != max && shortest_path[u] != max && shortest_path[u] + weight < shortest_path[v]) {
                std::cerr << "error\n";
                return {};
            }
        }
    }

    return shortest_path;
}

std::vector<int> bellman_ford_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size) {
    int max = 2147483647;
    std::vector<int> shortest_path(size, max);
    shortest_path[start] = 0;

    const std::vector<Edge>* adjacency = graph.getList();

    for (int i = 1; i <= size - 1; i++) {
        for (int u = 0; u < size; u++) {
            for (const Edge& edge : adjacency[u]) {
                int v = edge.end;
                int weight = edge.weight;
                if (shortest_path[u] != max && shortest_path[u] + weight < shortest_path[v]) {
                    shortest_path[v] = shortest_path[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < size; u++) {
        for (const Edge& edge : adjacency[u]) {
            int v = edge.end;
            int weight = edge.weight;
            if (shortest_path[u] != max && shortest_path[u] + weight < shortest_path[v]) {
                std::cerr << "error\n";
                return {};
            }
        }
    }

    return shortest_path;
}