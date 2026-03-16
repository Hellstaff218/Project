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

	test_isSorted_ascending();
	test_isSorted_descending();
	test_isSorted_unsorted();

	test_selectionSort_ascending();
	test_selectionSort_descending();
	test_selectionSort_sortedInput();

	test_insertionSort_ascending();
	test_insertionSort_descending();
	test_insertionSort_sortedInput();

	return 0;
}
