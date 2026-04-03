#include <iostream>
#include <iomanip>
#include "bit_operations.h"
#include "file_operations.h"
#include "box.h"

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
		std::cout << "================ SW_2 ================" << std::endl;
		std::cout << "Задания по побитовым операциям над числами" << std::endl;
		std::cout << "=== Тест swapHalfWord и cycleShift ===" << std::endl;

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
		std::cout << "\n=== Тест getMaxBit ===" << std::endl;

		int ar1[5] = {-1, 0xFFFF, 0x00, 0x7F, 0x10101010};
		int ar2[5] = {-1, -2, -3, -4, -5};

		std::cout << "getMaxBit(ar1) = " << std::dec << getMaxBit(ar1, 5) << std::endl;
		std::cout << "getMaxBit(ar2) = " << std::dec << getMaxBit(ar2, 5) << std::endl;
	}

	{
		std::cout << "\n================ SW_3 ================" << std::endl;
		std::cout << "Задания по побитовым операциям над массивами и работе с файлами" << std::endl;
		std::cout << "\n=== Тест cycleShiftArray: простой пример ===" << std::endl;

		int ar[4] = {0x40, 0x00, 0x80, 0x01};
		std::cout << "Before shift: ";
		printArray(ar, 4);
		cycleShiftArray(ar, 4, 1, true);
		std::cout << "After shift:  ";
		printArray(ar, 4);
	}

	{
		std::cout << "\n=== Тест cycleShiftArray: с установленным старшим битом ===" << std::endl;

		int ar[4] = {static_cast<int>(0x80000001), 0x00, 0x80, 0x10};
		std::cout << "Before shift: ";
		printArray(ar, 4);
		cycleShiftArray(ar, 4, 1, true);
		std::cout << "After shift:  ";
		printArray(ar, 4);
	}

	{
		std::cout << "\n=== Тест setBit и clearBit ===" << std::endl;

		int number = 0x0F;
		setBit(&number, 8);
		std::cout << "After setBit(8):   0x" << std::hex << number << std::endl;

		clearBit(&number, 1);
		std::cout << "After clearBit(1): 0x" << std::hex << number << std::endl;
	}

	{
		std::cout << "\n=== Тест fillFile ===" << std::endl;
		std::cout << "Запись данных в файл test.txt" << std::endl;
		fillFile("test.txt", 10, 20, '\t', 4, 12);
	}

	{
		std::cout << "\n================ ДОПОЛНИТЕЛЬНО ================" << std::endl;
		std::cout << "Тест записи и чтения структуры Box" << std::endl;
		std::cout << "\n=== Тест writeToFile и readFromFile ===" << std::endl;

		Box *temp = new Box();
		temp->_len = 1;
		temp->_width = 2;
		temp->_height = 3;
		temp->_color = 0x00FF00FF;

		writeToFile("temp.bin", *temp);
		delete temp;

		Box *temp1 = new Box();
		readFromFile("temp.bin", temp1);

		std::cout << "len    = " << temp1->_len << '\n';
		std::cout << "width  = " << temp1->_width << '\n';
		std::cout << "height = " << temp1->_height << '\n';
		std::cout << "color  = " << temp1->_color << '\n';

		readFromFile("temp.bin", nullptr);
	}
	return 0;
}
