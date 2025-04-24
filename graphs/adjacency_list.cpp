#include "include/adjacency_list.hpp"

void AdjacencyList::addEdge(int start, int end, int weight) {
    Edge edge = {weight, start, end};
    adj[start].push_back(edge); 
}

const std::vector<Edge>* AdjacencyList::getList() const {
    return adj;
}

void AdjacencyList::print() {
    for (int i = 0; i < Vertices; ++i) {
        std::cout << "\nVertex " << i << ":";
        for (const Edge& edge : adj[i])
            std::cout << " -> " << edge.end << " weight=" << edge.weight << "  ";
    }
    std::cout << std::endl;
}

void AdjacencyList::dumpToGraphviz() const {
    std::cout << "\ndigraph G {\n";
    for (int i = 0; i < Vertices; ++i) {
        for (const Edge& edge : adj[i]) {
            std::cout << edge.start << " -> " << edge.end << " [label=" << edge.weight << "];\n";
        }
    }
    std::cout << "}\n";
}
