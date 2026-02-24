#include "test_sorts.h"
#include "sorts.h"


bool checkSort(const int* ar, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (ar[i] > ar[i+1]) {
			return false;
		}
	}
	return true;

}

void test_selectionSort() {
	{
		int ar[4] = {5,4,3,2};
		selectionSort(ar, 4);
		if (checkSort(ar, 4) == true) {
			std::cout << "TEST PASSed" << std::endl;
		}
		else {
			std::cout << "TEST FAIL" << std::endl;
		}
	}

	{
		int ar[4] = {5,4,3,2};
		if (checkSort(ar, 4) == true) {
			std::cout << "TEST PASSed" << std::endl;
		}
		else {
			std::cout << "TEST FAIL" << std::endl;
		}
	}

}
