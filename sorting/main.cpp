#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <filesystem>

#include "algorythms/heapsort.cpp"
#include "algorythms/insertionsort.cpp"
#include "algorythms/introsort.cpp"
#include "algorythms/quicksort.cpp"
#include "algorythms/timsort.cpp"

#include "algorythms/include/heapsort.hpp"
#include "algorythms/include/insertionsort.hpp"
#include "algorythms/include/introsort.hpp"
#include "algorythms/include/quicksort.hpp"
#include "algorythms/include/timsort.hpp"

#include "timings_test.cpp"
#include "timings_test.hpp"
#include "test.cpp"
#include "test.hpp"

void time_check(int size, float sort_percentage){
    auto tab = std::make_unique<std::vector<int>>(size);

    for (int i = 0; i < size; i++) {
        (*tab)[i] = std::rand() % 10000;
    }
    if(sort_percentage == 2)
        std::sort(tab->begin(), tab->begin() + size, std::greater<int>());
    else if (sort_percentage > 0)
        std::sort(tab->begin(), tab->begin() + int(sort_percentage * size));

    std::ostringstream filename;
    filename << size << "_" << std::fixed << std::setprecision(3) << sort_percentage << ".csv";

    measure_sorting_timings(tab->data(), size, heapsort, "results/heapsort_" + filename.str());
    measure_sorting_timings(tab->data(), size, timsort, "results/timsort_" + filename.str());
    measure_sorting_timings(tab->data(), size, introsort, "results/introsort_" + filename.str());
}

int main() {
    const int SIZES[] = {1000, 10000, 50000, 100000, 500000, 1000000}; //sizes for the tables
    const float SORT_PERCENTAGE[] = {0, 0.25, 0.50, 0.75, 0.95, 0.99, 0.997, 1, 2}; //percantage of the table that is sorted
    
    for(int size : SIZES){
        for(float sort_percentage : SORT_PERCENTAGE){
            time_check(size, sort_percentage);
        }
    }

    test_sorting_algorithm(heapsort, "Heapsort");
    test_sorting_algorithm(introsort, "Introsort");
    test_sorting_algorithm(timsort, "Timsort"); //testing algorytms

    return 0;
}