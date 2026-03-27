#include "bit_operations.h"

void swapHalfWord(unsigned int *words)
{
    if (words == nullptr)
    {
        return;
    }

    unsigned int value = *words;

    unsigned int lowHalf = value & 0x0000FFFF;
    unsigned int highHalf = value & 0xFFFF0000;

    *words = (lowHalf << 16) | (highHalf >> 16);
}

void cycleShift(int *number, int N, int left)
{
    if (number == nullptr)
    {
        return;
    }
    const int bitCount = 32;
    unsigned int value = static_cast<unsigned int>(*number);

    N %= bitCount;
    if (N < 0)
    {
        N += bitCount;
    }
    if (N == 0)
    {
        return;
    }

    if (left == 1)
    {
        value = (value << N) | (value >> (bitCount - N));
    }
    else
    {
        value = (value >> N) | (value << (bitCount - N));
    }
    *number = static_cast<int>(value);
}

int getMaxBit(const int *array, int N)
{
    if (array == nullptr || N <= 0)
    {
        return -1;
    }

    int maxIndex = -1;
    unsigned char maxCount = 0;

    for (int i = 0; i < N; i++)
    {
        if (array[i] < 0)
        {
            continue;
        }

        unsigned char currentCount = getCount1Bit(array[i]);

        if (maxIndex == -1 || currentCount > maxCount)
        {
            maxCount = currentCount;
            maxIndex = i;
        }
    }

    return maxIndex;
}

unsigned char getCount1Bit(int number)
{

    int count = 0;
    while (number)
    {
        count += number & 1;
        number >>= 1;
    }
    return count;
}
