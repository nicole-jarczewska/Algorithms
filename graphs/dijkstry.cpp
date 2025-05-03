#include "include/dijkstry.hpp"

void DumpToGraphviz(int end, const std::vector<int>& path) {
    std::vector<int> result_path;
    for (int at = end; at != -1; at = path[at])
        result_path.push_back(at);
    std::reverse(result_path.begin(), result_path.end());

    for (size_t i = 0; i + 1 < result_path.size(); ++i) {
        std::cout << result_path[i] << " -> " << result_path[i + 1] << " [color=red];\n";
    }
    //std::cout << "}\n";
}

std::vector<int> dijkstra_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag) {
    std::vector<int> shortest_path(size, 2147483647);
    std::vector<int> path(size, -1);
    shortest_path[start] = 0;

    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> queue;
    queue.push({0, start});

    while (!queue.empty()) {
        int d = queue.top().first;
        int u = queue.top().second;
        queue.pop();

        if (!visited[u]) {
            for (int v = 0; v < size; v++) {
                int weight = graph.getWeight(u, v);
                if (weight > 0 && shortest_path[u] + weight < shortest_path[v]) {
                    shortest_path[v] = shortest_path[u] + weight;
                    path[v] = u; 
                    queue.push({shortest_path[v], v});
                }
            }
            visited[u] = true;
        }
    }

    if(testFlag){
        DumpToGraphviz(size-1, path);
    }

    return shortest_path;
}

std::vector<int> dijkstra_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag) {
    std::vector<int> shortest_path(size, 2147483647);
    std::vector<int> path(size, -1);
    shortest_path[start] = 0;

    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> queue;
    queue.push({0, start});

    Edge** adjacency = graph.getList();

    while (!queue.empty()) {
        int d = queue.top().first;
        int u = queue.top().second;
        queue.pop();

        if (!visited[u]) {
            int edgeCount = graph.getSize(u);
            for (int i = 0; i < edgeCount; ++i) {
                const Edge& edge = adjacency[u][i];
                int v = edge.end;

                if (shortest_path[u] + edge.weight < shortest_path[v]) {
                    shortest_path[v] = shortest_path[u] + edge.weight;
                    path[v] = u;
                    queue.push({shortest_path[v], v});
                }
            }
            visited[u] = true;
        }
    }

    if (testFlag) {
        DumpToGraphviz(size - 1, path);  // Make sure to define this
    }

    results = path;  // optional if needed

    return shortest_path;
}