#include <iostream>
#include <iomanip>
#include "bit_operations.h"

void printArray(const int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << std::hex << array[i] << " ";
	}
	std::cout << std::dec << std::endl;
}

int main()
{

	{
		unsigned int words1 = 0xFFAABBCC;
		unsigned int words2 = 0x01020304;

		std::cout << "Before swap:" << std::endl;
		std::cout << "words1 = 0x" << std::hex << std::uppercase << words1 << std::endl;
		std::cout << "words2 = 0x" << std::hex << std::uppercase << words2 << std::endl;

		swapHalfWord(&words1);
		swapHalfWord(&words2);

		std::cout << "After swap:" << std::endl;
		std::cout << "words1 = 0x" << std::hex << std::uppercase << words1 << std::endl;
		std::cout << "words2 = 0x" << std::hex << std::uppercase << words2 << std::endl;

		int number = 0x00004000;
		std::cout << "start = 0x" << std::hex << std::uppercase << number << std::endl;

		cycleShift(&number, 1, 0);
		std::cout << "shift right 1 = 0x" << std::hex << number << std::endl;

		cycleShift(&number, 2, 0);
		std::cout << "shift right 2 = 0x" << std::hex << number << std::endl;

		cycleShift(&number, 3, 1);
		std::cout << "shift left 3 = 0x" << std::hex << number << std::endl;
	}

	{
		int ar1[5] = {-1, 0xFFFF, 0x00, 0x7F, 0x10101010};
		int ar2[5] = {-1, -2, -3, -4, -5};

		std::cout << std::dec << getMaxBit(ar1, 5) << std::endl;
		std::cout << std::dec << getMaxBit(ar2, 5) << std::endl;
	}

	{
		int ar[4] = {0x40, 0x00, 0x80, 0x01};
		cycleShiftArray(ar, 4, 1, true);
		printArray(ar, 4);
	}

	{
		int ar[4] = {static_cast<int>(0x80000001), 0x00, 0x80, 0x10};
		cycleShiftArray(ar, 4, 1, true);
		printArray(ar, 4);
	}

	{
		int number = 0x0F;
		setBit(&number, 8);
		std::cout << std::hex << number << std::endl;

		clearBit(&number, 1);
		std::cout << std::hex << number << std::endl;
	}

	return 0;
}
