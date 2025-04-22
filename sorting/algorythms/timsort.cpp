#include <iostream>

#include "include/timsort.hpp"
#include "include/insertionsort.hpp"

const int RUN = 32; //run size

void merge(int* tab,int start,int middle,int end) {
    int left_size = middle - start + 1; //sizes of the tables we want to merge
    int right_size = end - middle;

    int* left_tab = new int[left_size]; //temporary tables
    int* right_tab = new int[right_size];

    
    for (int i = 0; i < left_size; i++)
        left_tab[i] = tab[start + i];
    for (int j = 0; j < right_size; j++)
        right_tab[j] = tab[middle + 1 + j];// copy data

    int i = 0, j = 0, k = start;

    while (i < left_size && j < right_size) {
        if (left_tab[i] <= right_tab[j]) {
            tab[k] = left_tab[i];
            i++;
        }
        else {
            tab[k] = right_tab[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        tab[k] = left_tab[i];
        i++;
        k++;
    }

    while (j < right_size) {
        tab[k] = right_tab[j];
        j++;
        k++;
    }
}

void timsort(int* tab, int size) 
{ 
    for (int i = 0; i < size; i += RUN) 
        insertionsort(tab, i, std::min((i + RUN - 1), (size - 1))); 
  
    for (int run_size = RUN; run_size < size; run_size = 2 * run_size) { 
        for (int left = 0; left < size; left += 2 * run_size) { 
  
            int mid = left + run_size - 1; 
            int right = std::min((left + 2 * run_size - 1), (size - 1)); 

            if (mid < right) 
                merge(tab, left, mid, right); 
        } 
    } 
} 

