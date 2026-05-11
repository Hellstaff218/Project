#include "sorts.h"
void selectionSort(int* ar, unsigned int size, bool ascending) {
	for (int i=1;i<size;i++) {
		int j = i - 1;
		int key =ar[i];
	 while (j >= 0 && (ascending ? ar[j] > key : ar[j] < key)) {
            ar[j + 1] = ar[j];
            j--;
        }
        ar[j + 1] = key;
    }
}

int isSorted(const int* array, unsigned int size)
 { bool ascending=true;
 bool descending=true;
 if (size <= 1) return 1;
 for (int i=0;i<size-1;i++) {
	if (array[i]>array[i+1])
		ascending=false;
	else if (array[i]<array[i+1])
		descending = false;	 
	}
	if (ascending) 
		return 1;
	if (descending)
		return -1;
	return 0;

}
