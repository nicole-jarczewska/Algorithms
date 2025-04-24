#include "algorythms/include/heapsort.hpp"
#include "algorythms/include/insertionsort.hpp"
#include "algorythms/include/introsort.hpp"
#include "algorythms/include/quicksort.hpp"
#include "algorythms/include/timsort.hpp"

#include "timings_test.hpp"

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <experimental/filesystem>

class Timer
{
  public:
    void start() { start_time = std::chrono::high_resolution_clock::now(); }
    void stop() { end_time = std::chrono::high_resolution_clock::now(); }
    long long nanoseconds() const { 
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count(); 
    }
  private:
    std::chrono::high_resolution_clock::time_point start_time, end_time;
};

struct TimingData { double ns; };

using Timings = std::vector<TimingData>;

class TimingsCollector {
  public:
    void add_timing(double nanoseconds) { timings.push_back({nanoseconds}); }
    
    bool save_file(const std::filesystem::path& filepath) const {
        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << std::endl;
            return false;
        }
        for (const auto& entry : timings)
            file << entry.ns << "\n";
        return true;
    }

    Timings get_timings() const { return timings; }

  private:
    Timings timings;
};

void measure_sorting_timings(const int* original_tab, int size, void (*sort_function)(int*, int), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100; // Sorting repeated 100 times for accuracy

    for (int i = 0; i < repeats; ++i) {
        std::vector<int> temp_tab(original_tab, original_tab + size); // Copy array before sorting
        timer.start();
        sort_function(temp_tab.data(), size);
        timer.stop();
        timingsCollector.add_timing(size, timer.nanoseconds());
    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error saving timings to " << output_csv << std::endl;
}
