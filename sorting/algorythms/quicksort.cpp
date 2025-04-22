#include <iostream>
#include <algorithm>
#include <cmath>

#include "include/quicksort.hpp"

int quicksort(int* tab, int start, int end) { 
    //start - index of the first element of the current table, end - index of last element 
    if (start >= end) return 0; //safety measure

    int pivot = tab[(start + end) / 2]; //pivot fixed as the middle element
    int i = start;
    int j = end;

    while (i <= j) {
        while (tab[i] < pivot) i++;
        while (tab[j] > pivot) j--;
        if (i <= j) {
            std::swap(tab[i], tab[j]);
            i++;
            j--;
        }
    }

    //if (j > start) quicksort(tab, start, j);
    //if (i < end) quicksort(tab, i, end);
    return i;
}