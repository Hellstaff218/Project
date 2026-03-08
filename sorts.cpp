#include "sorts.h"

int getMax(const int *ar, int size)
{
	int ind_max = 0;
	for (int i = 1; i < size; i++)
	{
		if (ar[ind_max] < ar[i])
		{
			ind_max = i;
		}
	}
	return ind_max;
}

void selectionSort(int *ar, unsigned int size, bool ascending)
{
	for (int i = 0; i < size; i++)
	{
		int indMax = getMax(&ar[ascending == true ? 0 : i], size - i);
		std::swap(ar[ascending == true ? indMax : indMax + i], ar[ascending == true ? size - i - 1 : i]);
	}
}

void insertionSort(int *ar, unsigned int size, bool ascending)
{
	for (unsigned int i = 1; i < size; i++)
	{
		int key = ar[i];
		int j = i - 1;
		if (ascending)
		{
			while (j >= 0 && ar[j] > key)
			{
				ar[j + 1] = ar[j];
				j--;
			}
		}
		else
		{
			while (j >= 0 && ar[j] < key)
			{
				ar[j + 1] = ar[j];
				j--;
			}
		}

		ar[j + 1] = key;
	}
}