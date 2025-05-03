#pragma once

std::vector<int> dfs_matrix(const AdjacencyMatrix& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag);

std::vector<int> dfs_list(const AdjacencyList& graph, std::vector<int>& results, int start, std::vector<bool>& visited, int size, bool testFlag);
