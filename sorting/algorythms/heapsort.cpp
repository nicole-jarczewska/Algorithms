#include <iostream>

#include "include/heapsort.hpp"

void make_heap(int* tab, int current_size, int i) {
    int largest = i; //asigning parent node as the largest
    int left = 2 * i + 1; // index of left child 
    int right = 2 * i + 2; // index of right child

    if (left < current_size && tab[left] > tab[largest])
        largest = left;

    if (right < current_size && tab[right] > tab[largest])
        largest = right;

    if (largest != i) {
        std::swap(tab[i], tab[largest]);// if parent isnt larger than children, swap
        make_heap(tab, current_size, largest);
    }
}

void heapsort(int* tab, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        make_heap(tab, size, i);
   
    for (int i = size - 1; i > 0; i--) {
        std::swap(tab[0], tab[i]); // move current root to end
        make_heap(tab, i, 0);
    }
}

