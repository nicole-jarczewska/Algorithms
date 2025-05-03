#pragma once

void DumpToGraphviz2(int size, const std::vector<int>& path);

std::vector<int> bellman_ford_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag);

std::vector<int> bellman_ford_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag);

