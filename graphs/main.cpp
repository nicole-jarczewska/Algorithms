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

void measure_time_matrix(int size, float density, const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        AdjacencyMatrix graph = load_matrix(size, density);
        timer.start();
        std::vector<bool> visited(size, false);
        //dfs_matrix(graph, 0, visited, size);
        dijkstra_matrix(graph, 0, visited, size);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());

    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error saving timings to " << output_csv << std::endl;

        AdjacencyMatrix graph = load_matrix(size, density);
        std::vector<bool> visited(size, false);
        auto dist = dijkstra_matrix(graph, 0, visited, size);
        for (int i = 0; i < dist.size(); ++i)
            std::cout << "Distance from 0 to " << i << " is " << dist[i] << "\n";

        graph.dumpToGraphviz();
}

void measure_time_list(int size, float density, const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        AdjacencyList graph = load_list(size, density);
        timer.start();
        std::vector<bool> visited(size, false);
        //dfs_matrix(graph, 0, visited, size);
        dijkstra_list(graph, 0, visited, size);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());

    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error saving timings to " << output_csv << std::endl;

        AdjacencyList graph = load_list(size, density);
        std::vector<bool> visited(size, false);
        auto dist = dijkstra_list(graph, 0, visited, size);
        for (int i = 0; i < dist.size(); ++i)
            std::cout << "Distance from 0 to " << i << " is " << dist[i] << "\n";

        graph.dumpToGraphviz();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int SIZES[] = {10}; //50, 100, 200, 500
    float DENSITIES[] = {0.25}; //0.50, 0.75, 1.0

    
    
    for (int size : SIZES)
        for(float density : DENSITIES){
            std::ostringstream filename;
            filename << size << "_" << std::fixed << std::setprecision(2) << density << ".csv";
            measure_time_list(size, density, std::filesystem::path("results/matrix_" + filename.str()));
    }

    // std::vector<bool> visited(size, false);
    // dfs_matrix(graph, 0, visited, size);

    // std::vector<bool> visited(size, false);
    // dfs_list(graph, 0, visited);

    return 0;
}