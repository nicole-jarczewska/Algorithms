#include "include/adjacency_list.hpp"

AdjacencyList::AdjacencyList(int size) : Vertices(size) {
    edges = new Edge*[Vertices];
    sizes = new int[Vertices];
    capacities = new int[Vertices];

    for (int i = 0; i < Vertices; ++i) {
        sizes[i] = 0;
        capacities[i] = 2;
        edges[i] = new Edge[capacities[i]];
    }
}


AdjacencyList& AdjacencyList::operator=(const AdjacencyList& other) {
    if (this == &other) return *this;

    for (int i = 0; i < Vertices; ++i)
        delete[] edges[i];
    delete[] edges;
    delete[] sizes;
    delete[] capacities;

    Vertices = other.Vertices;
    edges = new Edge*[Vertices];
    sizes = new int[Vertices];
    capacities = new int[Vertices];

    for (int i = 0; i < Vertices; ++i) {
        sizes[i] = other.sizes[i];
        capacities[i] = other.capacities[i];
        edges[i] = new Edge[capacities[i]];
        for (int j = 0; j < sizes[i]; ++j)
            edges[i][j] = other.edges[i][j];
    }

    return *this;
}

AdjacencyList::~AdjacencyList() {
    for (int i = 0; i < Vertices; ++i)
        delete[] edges[i];
    delete[] edges;
    delete[] sizes;
    delete[] capacities;
}

void AdjacencyList::addEdge(int start, int end, int weight) {
    if (start < 0 || start >= Vertices) return;

    if (sizes[start] >= capacities[start]) {
        capacities[start] *= 2;
        Edge* newList = new Edge[capacities[start]];
        for (int i = 0; i < sizes[start]; ++i)
            newList[i] = edges[start][i];
        delete[] edges[start];
        edges[start] = newList;
    }

    edges[start][sizes[start]++] = {weight, start, end};
}

Edge** AdjacencyList::getList() const {
    return edges;
}

int AdjacencyList::getSize(int v) const {
    if (v < 0 || v >= Vertices) return 0;
    return sizes[v];
}

void AdjacencyList::print() const {
    for (int i = 0; i < Vertices; ++i) {
        std::cout << "\nVertex " << i << ":";
        for (int j = 0; j < sizes[i]; ++j) {
            const Edge& e = edges[i][j];
            std::cout << " -> " << e.end << " weight=" << e.weight;
        }
    }
    std::cout << std::endl;
}


void AdjacencyList::dumpToGraphviz() const {
    std::cout << "\ndigraph G {\n";
    for (int i = 0; i < Vertices; ++i) {
        for (int j = 0; j < sizes[i]; ++j) {
            const Edge& e = edges[i][j];
            std::cout << e.start << " -> " << e.end << " [label=" << e.weight << "];\n";
        }
    }
    //std::cout << "}\n";
}

AdjacencyList AdjacencyList::makeGraph(int size, float density, bool flag) {
    AdjacencyList graph(size);
    int maxEdges = (size * (size - 1) / 2) * density;
    int weight;

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
        do{
        if (flag) weight = (rand() % 21) - 10;
        else weight = (rand() % 10) + 1;
        }while(weight==0);
        graph.addEdge(u, v, weight);
    }

    for (int edges = 0; edges < maxEdges - (size - 1); edges++) {
        int u, v;
        do {
            u = rand() % size;
            v = rand() % size;
        } while (u == v); 
        do{
            if (flag) weight = (rand() % 21) - 10;
            else weight = (rand() % 10) + 1;
            }while(weight==0);
        graph.addEdge(u, v, weight);
    }

    return graph;
}