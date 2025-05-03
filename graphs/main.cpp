#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <optional>
#include <ctime>
#include <chrono>
#include <queue>
#include <random>

#include "timer.cpp"
#include "include/timer.hpp"

#include "adjacency_matrix.cpp"
#include "include/adjacency_matrix.hpp"
#include "adjacency_list.cpp"
#include "include/adjacency_list.hpp"

#include "dfs.cpp"
#include "include/dfs.hpp"
#include "dijkstry.cpp"
#include "include/dijkstry.hpp"
#include "bellman_ford.cpp"
#include "include/bellman_ford.hpp"


void measure_time_matrix(int size, float density, std::vector<int> 
    (*function)(const AdjacencyMatrix&, std::vector<int>&, int, std::vector<bool>&, int, bool), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        {
        bool flag = false;
            if(function==bellman_ford_matrix) flag = true;
        AdjacencyMatrix graph = graph.makeGraph(size, density, flag);
        std::vector<bool> visited(size, false);
        std::vector<int> results;
        timer.start();
        function(graph, results, 0, visited, size, false);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
        }
    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error with " << output_csv << std::endl;
}

void measure_time_list(int size, float density, std::vector<int> 
    (*function)(const AdjacencyList&, std::vector<int>&, int, std::vector<bool>&, int, bool), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        {
        bool flag = false;
            if(function==bellman_ford_list) flag = true;
        AdjacencyList graph(size);
        graph = graph.makeGraph(size, density, flag);
        std::vector<bool> visited(size, false);
        std::vector<int> results;
        timer.start();
        function(graph, results, 0, visited, size, false);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
        }
    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error with " << output_csv << std::endl;
}

void test_matrix(int size, float density, std::vector<int> 
    (*function)(const AdjacencyMatrix&, std::vector<int>&, int, std::vector<bool>&, int, bool)) 
{
    AdjacencyMatrix graph(size);
    bool flag = false;
        if(function==bellman_ford_matrix) flag = true;
    graph = graph.makeGraph(size, density, flag);
    graph.dumpToGraphviz();

    std::vector<bool> visited(size, false);
    std::vector<int> results;
    auto result = function(graph, results, 0, visited, size, true);

    if(function==dfs_matrix){
        for (size_t i = 0; i + 1 < result.size()+1; i++){
        std::cout << result[i] << "[label=\"" << result[i] << " (" << i+1 << ")\"]" << std::endl;
        }
    }

    std::cout << "}\n"; 
}

void test_list(int size, float density, std::vector<int> 
    (*function)(const AdjacencyList&, std::vector<int>&, int, std::vector<bool>&, int, bool)) 
{
    AdjacencyList graph(size);
    bool flag = false;
        if(function==bellman_ford_list) flag = true;
    graph = graph.makeGraph(size, density, flag);
    graph.dumpToGraphviz();

    std::vector<bool> visited(size, false);
    std::vector<int> results;
    auto result = function(graph, results, 0, visited, size, true);

    if(function==dfs_list){
        for (size_t i = 0; i + 1 < result.size()+1; i++){
        std::cout << result[i] << "[label=\"" << result[i] << " (" << i+1 << ")\"]" << std::endl;
        }
    }

    std::cout << "}\n"; 
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int SIZES[] = {10, 50, 100, 200, 500};
    float DENSITIES[] = {0.25, 0.50, 0.75, 1.0};

    for (int size : SIZES){
        for(float density : DENSITIES){
            std::ostringstream filename;
            filename << size << "_" << std::fixed << std::setprecision(2) << density << ".csv";
            measure_time_matrix(size, density, dfs_matrix, std::filesystem::path("results/dfs_matrix_" + filename.str()));
            measure_time_matrix(size, density, dijkstra_matrix, std::filesystem::path("results/dijkstry_matrix_" + filename.str()));
            measure_time_matrix(size, density, bellman_ford_matrix, std::filesystem::path("results/bellman_ford_matrix_" + filename.str()));
            measure_time_list(size, density, dfs_list, std::filesystem::path("results/dfs_list_" + filename.str()));
            measure_time_list(size, density, dijkstra_list, std::filesystem::path("results/dijkstry_list_" + filename.str()));
            measure_time_list(size, density, bellman_ford_list, std::filesystem::path("results/bellman_ford_list_" + filename.str()));
        }
    }

    {
        int size = 10;
        int density = 0.25;
        test_matrix(size, density, dfs_matrix);
        test_matrix(size, density, dijkstra_matrix);
        test_matrix(size, density, bellman_ford_matrix);
        test_list(size, density, dfs_list);
        test_list(size, density, dijkstra_list);
        test_list(size, density, bellman_ford_list);
    }
    
    return 0;
}