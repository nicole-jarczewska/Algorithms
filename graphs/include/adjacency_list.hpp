#pragma once

class AdjacencyList {
public:
    AdjacencyList(int vertices) : Vertices(vertices) {}
    
    void addEdge(int start, int end, int weight);
    const std::vector<Edge>* getList() const;
    void print();
    void dumpToGraphviz() const;


private:
    int Vertices;
    std::vector<Edge> edges[100];
};