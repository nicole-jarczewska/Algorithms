#include "include/timer.hpp"

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