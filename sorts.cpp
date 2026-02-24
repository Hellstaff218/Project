#include "sorts.h"


int getMax(const int* ar, int size) {
	int ind_max = 0;
	for (int i = 1; i < size; i++) {
		if (ar[ind_max] < ar[i]) {
			ind_max = i;
		}
	}
	return ind_max;
}


void selectionSort(int* ar, int size) {
	for (int i = 0; i < size; i++) {
		int indMax = getMax(ar, size - i);
		std::swap(ar[size - i - 1], ar[indMax]);
	}
}

void selSt(int *r, int s, bool a) {
	for (int i = 0; i < s; i++) {
		int indMax = getMax(&r[a == true ? 0 : i], s - i);
		std::swap(r[a == true ? indMax : indMax + i], r[a == true ? s - i - 1 : i]);
	}
}
