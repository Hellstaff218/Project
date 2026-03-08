#include <iostream>

#include "sorts.h"
#include "test_sorts.h"

void showArray(const int *ar, int size, char format)
{
	switch (format)
	{
	// 1 2 3 4 5 6 7 8 9 A B C D E F
	case 'H':
	case 'h':
		std::cout << std::hex;
		break;
	case 'D':
	case 'd':
		std::cout << std::dec;
		break;
	default:
		std::cout << "unknown format for out, set default as decimal" << std::endl;
		std::cout << std::dec;
		break;
	}

	for (int i = 0; i < size; i++)
	{
		std::cout << ar[i] << " ";
	}
	std::cout << std::dec << std::endl;
}

int main(int argc, char **argv)
{

	test_selectionSort();

	// return 0;
	int ar[10] = {-12, 16, 1, 24, 5, 6, 4, 12, 10, 8};
	getMax(ar, 10);

	// selectionSort(ar, 10, true);
	insertionSort(ar, 10, true);
	showArray(ar, 10, 'd');

	// selectionSort(ar, 10, false);
	insertionSort(ar, 10, true);
	showArray(ar, 10, 'd');

	return 0;
}
