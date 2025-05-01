#pragma once

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
    int getWeight(int u, int v) const;
    void print() const;
    void dumpToGraphviz() const;
    Matrix getMatrix() const;
    void setMatrix(const Matrix& newMatrix);
    AdjacencyMatrix makeGraph(int size, float density);

private:
    int size;
    Matrix matrix;
    std::vector<Edge> edges;
};