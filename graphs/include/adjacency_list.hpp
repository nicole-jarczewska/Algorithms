#pragma once

class AdjacencyList {
public:
    AdjacencyList(int size);
    AdjacencyList& operator=(const AdjacencyList& other);
    ~AdjacencyList();

    void addEdge(int start, int end, int weight);
    void print() const;
    void dumpToGraphviz() const;

    static AdjacencyList makeGraph(int size, float density, bool flag);
    Edge** getList() const;
    int getSize(int v) const;

private:
    int Vertices;
    Edge** edges;       
    int* sizes;          
    int* capacities;
    };