#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "algorythms/include/heapsort.hpp"
#include "algorythms/include/insertionsort.hpp"
#include "algorythms/include/introsort.hpp"
#include "algorythms/include/quicksort.hpp"
#include "algorythms/include/timsort.hpp"

#include "test.hpp"


void test_sorting_algorithm(void (*sort_function)(int*, int), const std::string& name)
{
    int size = 100000;
    std::vector<int> tab(size);

    for (int i = 0; i < size; i++) {
        tab[i] = std::rand() % 10000;
    }

    std::vector<int> test_tab = tab; // copyign array to sort it
    std::sort(test_tab.begin(), test_tab.end());

    sort_function(tab.data(), size);

    if (tab == test_tab) {
        std::cout << name << " passed the test.\n";
    } else {
        std::cout << name << " failed the test.\n";
    }
}
