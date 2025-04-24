#pragma once

void measure_sorting_timings(const int* original_arr, int size, void (*sort_function)(int*, int), const std::filesystem::path& output_csv);