#include "test_sorts.h"
#include "sorts.h"

#pragma region Functions

bool checkSort(const int *ar, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (ar[i] > ar[i + 1])
		{
			return false;
		}
	}
	return true;
}

bool arraysEqual(const int *a, const int *b, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

void printArray(const int *ar, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
		std::cout << ar[i] << " ";

	std::cout << std::endl;
}

void printTestResult(const char *name, bool ok)
{
	std::cout << (ok ? "[PASS]" : "[FAIL]") << name << std::endl;
}

void printTestResult(
	const char *testName,
	const int *expected,
	const int *actual,
	unsigned int size)
{
	if (arraysEqual(expected, actual, size))
	{
		std::cout << "[PASS] " << testName << std::endl;
	}
	else
	{
		std::cout << "[FAIL] " << testName << std::endl;

		std::cout << "expected: ";
		printArray(expected, size);

		std::cout << "actual:   ";
		printArray(actual, size);
	}
}

#pragma endregion

#pragma region Tests

#pragma region isSorted

void test_isSorted_ascending()
{
	int ar[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int res = isSorted(ar, 10);

	if (res == 1)
	{
		std::cout << "[PASS] isSorted ascending" << std::endl;
	}
	else
	{
		std::cout << "[FAIL] isSorted ascending (got " << res << " expected 1)" << std::endl;
	}
}

void test_isSorted_descending()
{

	int ar[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int res = isSorted(ar, 10);

	if (res == -1)
	{

		std::cout << "[PASS] isSorted descending" << std::endl;
	}
	else
	{
		std::cout << "[FAIL] isSorted descending (got" << res << " expented -1)" << std::endl;
	}
}

void test_isSorted_unsorted()
{
	int ar[] = {5, 4, 3, 1, 10, 13, 16, 2, 7, 29};
	int res = isSorted(ar, 10);

	if (res == 0)
	{
		std::cout << "[PASS] isSorted unsorted" << std::endl;
	}
	else
	{
		std::cout << "[FAIL] isSorted unsorted (got" << res << " expented 0)" << std::endl;
	}
}

#pragma endregion

#pragma region Selection sort

void test_selectionSort_ascending()
{
	int ar[] = {5, 1, 4, 2, 8};
	int expected[] = {1, 2, 4, 5, 8};

	selectionSort(ar, 5, true);

	printTestResult("selectionSort ascending", expected, ar, 5);
}

void test_selectionSort_descending()
{
	int ar[] = {5, 1, 4, 2, 8};
	int expected[] = {8, 5, 4, 2, 1};

	selectionSort(ar, 5, false);

	printTestResult("selectionSort ascending", expected, ar, 5);
}

void test_selectionSort_sortedInput()
{
	int ar[] = {5, 1, 4, 2, 8};
	int expected[] = {1, 2, 4, 5, 8};

	selectionSort(ar, 5);
	printTestResult("selectionSort sortedInput", expected, ar, 5);
}

#pragma endregion

#pragma region Insertion sort

void test_insertionSort_ascending()
{
}

void test_insertionSort_descending()
{
}

void test_insertionSort_sortedInput()
{
}

#pragma endregion

#pragma endregion