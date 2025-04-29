#include "include/dijkstry.hpp"

std::vector<int> dijkstra_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size) {
    std::vector<int> shortest_path(size, 2147483647);
    shortest_path[start] = 0;

    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> queue;
    queue.push({0, start});

    while (!queue.empty()) {
        int d = queue.top().first;
        int u = queue.top().second;
        queue.pop();

        if (visited[u]==false){
            for (int v = 0; v < size; v++) {
                int weight = graph.getWeight(u, v);
                if (weight > 0 && shortest_path[u] + weight < shortest_path[v]) {
                    shortest_path[v] = shortest_path[u] + weight;
                    queue.push({shortest_path[v], v});
                }
            }
            visited[u] = true;
        }
    }

    return shortest_path;
}

std::vector<int> dijkstra_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size) {
    std::vector<int> shortest_path(size, 2147483647);
    shortest_path[start] = 0;

    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> queue;
    queue.push({0, start});

    while (!queue.empty()) {
        int d = queue.top().first;
        int u = queue.top().second;
        queue.pop();

        if (visited[u]==false){
            const std::vector<Edge>* list = graph.getList();

            for (const Edge& edge : list[u]) {
                int v = edge.end;

                if (shortest_path[u] + edge.weight < shortest_path[v]) {
                    shortest_path[v] = shortest_path[u] + edge.weight;
                    queue.push({shortest_path[v], v});
                }
            }
        visited[u] = true;
        }
    }

    return shortest_path;
}