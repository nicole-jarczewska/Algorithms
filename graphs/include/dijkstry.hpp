#pragma once

void DumpToGraphviz(int end, const std::vector<int>& path);

std::vector<int> dijkstra_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag);

std::vector<int> dijkstra_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag);
