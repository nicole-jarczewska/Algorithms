#pragma once

#include <vector>
#include <iostream>


struct Edge {
    int weight;
    int start;
    int end;
};

struct Matrix {
    int size;
    std::vector<int> data;

    Matrix(int s);
    void set(int row, int col, int value);
    int get(int row, int col) const;
    void print() const;
};

class AdjacencyMatrix {
public:
    AdjacencyMatrix(int size);

    void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);
    int getWeight(int u, int v) const;
    void print() const;
    void graphviz() const;
    Matrix getMatrix() const;
    void setMatrix(const Matrix& newMatrix);

private:
    int size;
    Matrix matrix;
    std::vector<Edge> edges;
};