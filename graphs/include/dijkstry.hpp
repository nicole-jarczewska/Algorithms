#pragma once

std::vector<int> dijkstra_matrix(const AdjacencyMatrix& graph, int start, std::vector<bool>& visited, int size);

std::vector<int> dijkstra_list(const AdjacencyList& graph, int start, std::vector<bool>& visited, int size)
