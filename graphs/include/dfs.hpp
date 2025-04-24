#pragma once

void dfs_matrix(const AdjacencyMatrix& graph, int start, std::vector<bool>& visited, int size);

void dfs_list(const AdjacencyList& graph, int start, std::vector<bool>& visited);
