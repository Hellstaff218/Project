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
    (void)number;
    (void)N;
    (void)left;
}

int getMaxBit(const int *array, int N)
{
    (void)array;
    (void)N;
    return 0;
}

unsigned char getCount1Bit(int number)
{
    (void)number;
    return 0;
}
