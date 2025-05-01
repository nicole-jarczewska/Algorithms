#include "include/adjacency_list.hpp"

void AdjacencyList::addEdge(int start, int end, int weight) {
    Edge edge = {weight, start, end};
    edges[start].push_back(edge); 
}

const std::vector<Edge>* AdjacencyList::getList() const {
    return edges;
}

AdjacencyList AdjacencyList::makeGraph(int size, float density) {
    AdjacencyList graph(size);
    int max_edges = (size * (size - 1) / 2) * density;

    std::vector<int> nodes;

    for (int i = 0; i < size; ++i) {
        nodes.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(nodes.begin() + 1, nodes.end(), g);

    for (int i = 0; i < size - 1; ++i) {
        int u = nodes[i];
        int v = nodes[i + 1];
        int weight = rand() % 10 + 1;
        graph.addEdge(u, v, weight);
    }

    for (int edges = 0; edges < max_edges-size+1; edges++) {
        int u, v;
            do {
                u = rand() % size;
                v = rand() % size;
            } while (u == v);
        graph.addEdge(u, v, rand() % 10 + 1);
    }

    return graph;
}

void AdjacencyList::print() {
    for (int i = 0; i < Vertices; ++i) {
        std::cout << "\nVertex " << i << ":";
        for (const Edge& edge : edges[i])
            std::cout << " -> " << edge.end << " weight=" << edge.weight << "  ";
    }
    std::cout << std::endl;
}

void AdjacencyList::dumpToGraphviz() const {
    std::cout << "\ndigraph G {\n";
    for (int i = 0; i < Vertices; ++i) {
        for (const Edge& edge : edges[i]) {
            std::cout << edge.start << " -> " << edge.end << " [label=" << edge.weight << "];\n";
        }
    }
    std::cout << "}\n";
}