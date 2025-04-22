#include <iostream>
#include <algorithm>
#include <cmath>

#include "include/insertionsort.hpp"

void insertionsort(int* tab, int start, int end)
{
    for (int i = start + 1; i <= end; i++) {
        int key = tab[i];
        int j = i - 1;

        while (j >= start && tab[j] > key) { //moving element to the right
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = key;
    }
}