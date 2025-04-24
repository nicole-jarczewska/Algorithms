#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <vector>
#include <optional>

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
    std::cout << "}\n";
}

Matrix AdjacencyMatrix::getMatrix() const {
    return matrix;
}

void AdjacencyMatrix::setMatrix(const Matrix& newMatrix) {
    matrix = newMatrix;
}