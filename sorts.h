#ifndef _sorts_h_
#define _sorts_h_

#include <iostream>

int getMax(const int *, int);

void selectionSort(int *ar, unsigned int size, bool ascending = true);

void insertionSort(int *ar, unsigned int size, bool ascending = true);

int isSorted(const int *array, unsigned int size);
#endif
