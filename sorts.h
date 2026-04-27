#ifndef _sorts_h_
#define _sorts_h_

bool lessComp(int left, int right);
bool greaterComp(int left, int right);

int getMax(const int *ar, int size);
int isSorted(const int *array, unsigned int size);

void bubbleSort(int *ar, int size, bool (*comp)(int, int));     //< пузырьковая сортировка
void selectionSort(int *ar, int size, bool (*comp)(int, int));  //< сортировка выбором
void insertionSort(int *ar, int size, bool (*comp)(int, int));  //< сортировка вставками
void mergeSort(int *ar, int size, bool (*comp)(int, int));      //< сортировка слиянием
void quickSort(int *ar, int size, bool (*comp)(int, int));      //< быстрая сортировка
void sortShell(int *ar, int size, bool (*comp)(int, int));      //< сортировка Шелла
void countSort(int *ar, int size, bool (*comp)(int, int));      //< сортировка подсчётом

void selectionSort(int *ar, unsigned int size, bool ascending = true);
void insertionSort(int *ar, unsigned int size, bool ascending = true);

#endif
