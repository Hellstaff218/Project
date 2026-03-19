#include <iostream>
#include <iomanip>
#include "bit_operations.h"

int main()
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

    return 0;
}
