#include "sorts.h"

#include <algorithm>
#include <vector>

namespace
{
bool isAscendingComp(bool (*comp)(int, int))
{
    return comp != nullptr && comp(1, 2);
}

void mergeSortImpl(int *ar, int left, int right, bool (*comp)(int, int), int *buffer)
{
    if (right - left <= 1)
    {
        return;
    }

    const int middle = left + (right - left) / 2;
    mergeSortImpl(ar, left, middle, comp, buffer);
    mergeSortImpl(ar, middle, right, comp, buffer);

    int leftIndex = left;
    int rightIndex = middle;
    int bufferIndex = 0;

    while (leftIndex < middle && rightIndex < right)
    {
        if (comp(ar[rightIndex], ar[leftIndex]))
        {
            buffer[bufferIndex++] = ar[rightIndex++];
        }
        else
        {
            buffer[bufferIndex++] = ar[leftIndex++];
        }
    }

    while (leftIndex < middle)
    {
        buffer[bufferIndex++] = ar[leftIndex++];
    }

    while (rightIndex < right)
    {
        buffer[bufferIndex++] = ar[rightIndex++];
    }

    for (int i = 0; i < bufferIndex; i++)
    {
        ar[left + i] = buffer[i];
    }
}

void quickSortImpl(int *ar, int left, int right, bool (*comp)(int, int))
{
    if (left >= right)
    {
        return;
    }

    int i = left;
    int j = right;
    const int pivot = ar[left + (right - left) / 2];

    while (i <= j)
    {
        while (comp(ar[i], pivot))
        {
            i++;
        }

        while (comp(pivot, ar[j]))
        {
            j--;
        }

        if (i <= j)
        {
            std::swap(ar[i], ar[j]);
            i++;
            j--;
        }
    }

    if (left < j)
    {
        quickSortImpl(ar, left, j, comp);
    }

    if (i < right)
    {
        quickSortImpl(ar, i, right, comp);
    }
}
}

bool lessComp(int left, int right)
{
    return left < right;
}

bool greaterComp(int left, int right)
{
    return left > right;
}

int getMax(const int *ar, int size)
{
    int indMax = 0;
    for (int i = 1; i < size; i++)
    {
        if (ar[indMax] < ar[i])
        {
            indMax = i;
        }
    }
    return indMax;
}

int isSorted(const int *array, unsigned int size)
{
    if (size < 2)
    {
        return 1;
    }

    bool increasing = true;
    bool decreasing = true;

    for (unsigned int i = 0; i < size - 1; i++)
    {
        if (array[i] < array[i + 1])
        {
            decreasing = false;
        }

        if (array[i] > array[i + 1])
        {
            increasing = false;
        }
    }

    if (increasing)
    {
        return 1;
    }

    if (decreasing)
    {
        return -1;
    }

    return 0;
}

void bubbleSort(int *ar, int size, bool (*comp)(int, int))
{
    if (ar == nullptr || size <= 1 || comp == nullptr)
    {
        return;
    }

    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (comp(ar[j + 1], ar[j]))
            {
                std::swap(ar[j], ar[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
        {
            return;
        }
    }
}

void selectionSort(int *ar, int size, bool (*comp)(int, int))
{
    if (ar == nullptr || size <= 1 || comp == nullptr)
    {
        return;
    }

    for (int i = 0; i < size - 1; i++)
    {
        int bestIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (comp(ar[j], ar[bestIndex]))
            {
                bestIndex = j;
            }
        }

        if (bestIndex != i)
        {
            std::swap(ar[i], ar[bestIndex]);
        }
    }
}

void insertionSort(int *ar, int size, bool (*comp)(int, int))
{
    if (ar == nullptr || size <= 1 || comp == nullptr)
    {
        return;
    }

    for (int i = 1; i < size; i++)
    {
        const int key = ar[i];
        int j = i - 1;

        while (j >= 0 && comp(key, ar[j]))
        {
            ar[j + 1] = ar[j];
            j--;
        }

        ar[j + 1] = key;
    }
}

void mergeSort(int *ar, int size, bool (*comp)(int, int))
{
    if (ar == nullptr || size <= 1 || comp == nullptr)
    {
        return;
    }

    std::vector<int> buffer(static_cast<std::size_t>(size));
    mergeSortImpl(ar, 0, size, comp, buffer.data());
}

void quickSort(int *ar, int size, bool (*comp)(int, int))
{
    if (ar == nullptr || size <= 1 || comp == nullptr)
    {
        return;
    }

    quickSortImpl(ar, 0, size - 1, comp);
}

void sortShell(int *ar, int size, bool (*comp)(int, int))
{
    if (ar == nullptr || size <= 1 || comp == nullptr)
    {
        return;
    }

    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            const int value = ar[i];
            int j = i;

            while (j >= gap && comp(value, ar[j - gap]))
            {
                ar[j] = ar[j - gap];
                j -= gap;
            }

            ar[j] = value;
        }
    }
}

void countSort(int *ar, int size, bool (*comp)(int, int))
{
    if (ar == nullptr || size <= 1 || comp == nullptr)
    {
        return;
    }

    int minValue = ar[0];
    int maxValue = ar[0];
    for (int i = 1; i < size; i++)
    {
        minValue = std::min(minValue, ar[i]);
        maxValue = std::max(maxValue, ar[i]);
    }

    std::vector<int> counts(static_cast<std::size_t>(maxValue - minValue + 1), 0);
    for (int i = 0; i < size; i++)
    {
        counts[static_cast<std::size_t>(ar[i] - minValue)]++;
    }

    int index = 0;
    if (isAscendingComp(comp))
    {
        for (int value = minValue; value <= maxValue; value++)
        {
            int &count = counts[static_cast<std::size_t>(value - minValue)];
            while (count > 0)
            {
                ar[index++] = value;
                count--;
            }
        }
    }
    else
    {
        for (int value = maxValue; value >= minValue; value--)
        {
            int &count = counts[static_cast<std::size_t>(value - minValue)];
            while (count > 0)
            {
                ar[index++] = value;
                count--;
            }
        }
    }
}

void selectionSort(int *ar, unsigned int size, bool ascending)
{
    selectionSort(ar, static_cast<int>(size), ascending ? lessComp : greaterComp);
}

void insertionSort(int *ar, unsigned int size, bool ascending)
{
    insertionSort(ar, static_cast<int>(size), ascending ? lessComp : greaterComp);
}
