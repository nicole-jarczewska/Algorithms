#include "include/adjacency_matrix.hpp"

Matrix::Matrix(int size) : size(size), data(size * size, 0) {}

void Matrix::set(int row, int col, int value) {
    data[row * size + col] = value;
}

int Matrix::get(int row, int col) const {
    return data[row * size + col];
}

void Matrix::print() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << get(i, j) << " ";
        }
        std::cout << "\n";
    }
}


AdjacencyMatrix::AdjacencyMatrix(int size) : size(size), matrix(size) {}

void AdjacencyMatrix::addEdge(int u, int v, int weight) {
    matrix.set(u, v, weight);

    auto it = std::find_if(edges.begin(), edges.end(), [&](const Edge& e) {
        return e.start == u && e.end == v;
    });

    if (it != edges.end()) {
        it->weight = weight;
    } else {
        edges.push_back({weight, u, v});
    }
}

int AdjacencyMatrix::getWeight(int u, int v) const {
    return matrix.get(u, v);
}

void AdjacencyMatrix::print() const {
    std::cout << "matrix:\n";
    matrix.print();
}

void AdjacencyMatrix::dumpToGraphviz() const {
    std::cout << "\ndigraph G {\n";
    for (const auto& e : edges) {
        std::cout << e.start << " -> " << e.end << " [label=" << e.weight << "]\n";
    }
    // std::cout << "}\n";
}

Matrix AdjacencyMatrix::getMatrix() const {
    return matrix;
}

void AdjacencyMatrix::setMatrix(const Matrix& newMatrix) {
    matrix = newMatrix;
}

AdjacencyMatrix AdjacencyMatrix::makeGraph(int size, float density, bool flag) {
    AdjacencyMatrix graph(size);
    int max_edges = (size * (size - 1) / 2) * density;
    int weight;

    std::vector<int> nodes;

    for(int i = 0; i < size; i++) {
        nodes.push_back(i);
    }
 
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(nodes.begin()+1, nodes.end(), g);

    for (int i = 0; i < size-1; ++i) {
        int u = nodes[i];
        int v = nodes[i + 1];
        do{
            if (flag) weight = (rand() % 21) - 10;
            else weight = (rand() % 10) + 1;
        }while(weight==0);
        graph.addEdge(u, v, weight);
    }

    for (int edges = 0; edges < max_edges+1-size; edges++) {
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