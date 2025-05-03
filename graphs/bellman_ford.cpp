#include "include/bellman_ford.hpp"


void DumpToGraphviz2(int end, const std::vector<int>& path) {
    std::vector<int> result_path;
    for (int at = end; at != -1; at = path[at])
        result_path.push_back(at);
    std::reverse(result_path.begin(), result_path.end());

    for (size_t i = 0; i + 1 < result_path.size(); ++i) {
        std::cout << result_path[i] << " -> " << result_path[i + 1] << " [color=red];\n";
    }
    //std::cout << "}\n";
}

std::vector<int> bellman_ford_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag) {
    int max = 2147483647;
    std::vector<int> shortest_path(size, max);
    std::vector<int> path(size, -1);
    shortest_path[start] = 0;

    Matrix matrix = graph.getMatrix();

    for (int i = 1; i <= size - 1; i++) {
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                int weight = matrix.get(u, v);
                if (weight != 0 && weight != max && shortest_path[u] != max && shortest_path[u] + weight < shortest_path[v]) {
                    shortest_path[v] = shortest_path[u] + weight;
                    path[v] = u; 
                }
            }
        }
    }

    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            int weight = matrix.get(u, v);
            if (weight != 0 && weight != max && shortest_path[u] != max && shortest_path[u] + weight < shortest_path[v]) {
                return {};
            }
        }
    }

    if(testFlag){
        DumpToGraphviz(size-1, path);
    }

    return shortest_path;
}

std::vector<int> bellman_ford_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag) {
    int max = 2147483647;
    std::vector<int> shortest_path(size, max);
    std::vector<int> path(size, -1);
    shortest_path[start] = 0;

    Edge** adjacency = graph.getList();

    for (int i = 1; i < size; ++i) {
        for (int u = 0; u < size; ++u) {
            int edgeCount = graph.getSize(u);
            for (int j = 0; j < edgeCount; ++j) {
                const Edge& e = adjacency[u][j];
                if (shortest_path[u] != max && shortest_path[u] + e.weight < shortest_path[e.end]) {
                    shortest_path[e.end] = shortest_path[u] + e.weight;
                    path[e.end] = u;
                }
            }
        }
    }

    for (int u = 0; u < size; ++u) {
        int edgeCount = graph.getSize(u);
        for (int j = 0; j < edgeCount; ++j) {
            const Edge& e = adjacency[u][j];
            if (shortest_path[u] != max && shortest_path[u] + e.weight < shortest_path[e.end]) {
                return {};
            }
        }
    }

    if (testFlag) {
        DumpToGraphviz2(size - 1, path);
    }

    return shortest_path;
}