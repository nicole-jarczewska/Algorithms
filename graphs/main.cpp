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


AdjacencyMatrix load_matrix(int size, float density){
    float limit = size * (size - 1) * density / 2;

    AdjacencyMatrix graph(size);
    for (int edges = 0; edges < limit; edges++) {
            int u, v;
                do {
                    u = rand() % size;
                    v = rand() % size;
                } while (u == v);
            graph.addEdge(u, v, rand() % 10 + 1);
        }
    
    return graph;
}

AdjacencyList load_list(int size, float density){
    float limit = size * (size - 1) * density / 2;

    AdjacencyList graph(size);
    for (int edges = 0; edges < limit; edges++) {
            int u, v;
                do {
                    u = rand() % size;
                    v = rand() % size;
                } while (u == v);
            graph.addEdge(u, v, rand() % 10 + 1);
        }

    return graph;
}

void measure_time_matrix(int size, float density, std::vector<int> 
    (*function)(const AdjacencyMatrix&, std::vector<int>&, int, std::vector<bool>&, int), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        {
        AdjacencyMatrix graph = load_matrix(size, density);
        timer.start();
        std::vector<bool> visited(size, false);
        std::vector<int> results;
        function(graph, results, 0, visited, size);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
        }
    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error with " << output_csv << std::endl;

        // AdjacencyMatrix graph = load_matrix(size, density);
        // std::vector<bool> visited(size, false);
        // std::vector<int> results;
        // auto dist = bellman_ford_matrix(graph, results, 0, visited, size);
        // for (int i = 0; i < dist.size(); ++i)
        //     std::cout << "Distance from 0 to " << i << " is " << dist[i] << "\n";

        // graph.dumpToGraphviz();
}

void measure_time_list(int size, float density, std::vector<int> 
    (*function)(const AdjacencyList&, std::vector<int>&, int, std::vector<bool>&, int), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        {
        AdjacencyList graph = load_list(size, density);
        timer.start();
        std::vector<bool> visited(size, false);
        std::vector<int> results;
        function(graph, results, 0, visited, size);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
        }
    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error with " << output_csv << std::endl;

        // AdjacencyList graph = load_list(size, density);
        // std::vector<bool> visited(size, false);
        // auto dist = dijkstra_list(graph, 0, visited, size);
        // for (int i = 0; i < dist.size(); ++i)
        //     std::cout << "Distance from 0 to " << i << " is " << dist[i] << "\n";

        // graph.dumpToGraphviz();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int SIZES[] = {10, 50, 100, 200}; //
    float DENSITIES[] = {0.25, 0.50, 0.75, 1.0}; 

    for (int size : SIZES){
        for(float density : DENSITIES){
            std::ostringstream filename;
            filename << size << "_" << std::fixed << std::setprecision(2) << density << ".csv";
            measure_time_matrix(size, density, dfs_matrix, std::filesystem::path("results/dfs_matrix_" + filename.str()));
            measure_time_matrix(size, density, dijkstra_matrix, std::filesystem::path("results/dijkstry_matrix_" + filename.str()));
            measure_time_matrix(size, density, bellman_ford_matrix, std::filesystem::path("results/bellman_ford_matrix_" + filename.str()));
            measure_time_list(size, density, dfs_list, std::filesystem::path("results/dfs_matrix_" + filename.str()));
            measure_time_list(size, density, dijkstra_list, std::filesystem::path("results/dijkstry_list_" + filename.str()));
            measure_time_list(size, density, bellman_ford_list, std::filesystem::path("results/bellman_ford_list_" + filename.str()));
        }
    }

    return 0;
}