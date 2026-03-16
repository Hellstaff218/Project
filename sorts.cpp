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

/**
 * @brief Проверяет массив на отсортированность.
 *
 * Функция анализирует порядок элементов массива и определяет,
 * отсортирован ли он по возрастанию или по убыванию.
 *
 * @param array Указатель на массив целых чисел.
 * @param size Размер массива.
 *
 * @return
 *  1  - массив отсортирован по возрастанию\n
 * -1  - массив отсортирован по убыванию\n
 *  0  - массив не отсортирован
 *
 * @note Если размер массива меньше 2, массив считается отсортированным.
 */
int isSorted(const int *array, unsigned int size)
{
	if (size < 2)
		return 1;

	bool increasing = true;
	bool decreasing = true;

	for (unsigned int i = 0; i < size - 1; i++)
	{
		if (array[i] < array[i + 1])
			decreasing = false;

		if (array[i] > array[i + 1])
			increasing = false;
	}

	if (increasing)
		return 1;

	if (decreasing)
		return -1;

	return 0;
}