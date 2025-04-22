#include <iostream>
#include <algorithm>
#include <cmath>

#include "include/insertionsort.hpp"
#include "include/heapsort.hpp"
#include "include/quicksort.hpp"
#include "include/introsort.hpp"

void introsort_recursive(int* tab, int start, int end, int max_depth) {
    int size = end - start + 1;

    if (size < 16) {
        insertionsort(tab, start, end); //inserionsort for small fragments
        return;
    }
    
    if (max_depth == 0) {
        heapsort(tab + start, size);
        return;
    }

    int pivot = quicksort(tab, start, end); //index of pivot
    
    if (start < pivot - 1) introsort_recursive(tab, start, pivot - 1, max_depth - 1);
    if (pivot < end) introsort_recursive(tab, pivot, end, max_depth - 1);
}

void introsort(int* tab, int size) {
    int max_depth = 2 * static_cast<int>(log2(size));
    introsort_recursive(tab, 0, size - 1, max_depth);
}