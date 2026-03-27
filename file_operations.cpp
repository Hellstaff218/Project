#include "file_operations.h"

#include <fstream>
#include <cstdlib>
#include <ctime>

void fillFile(const char *fileName, int min, int max, char delimeter, int cols, int countElements)
{
    if (fileName == nullptr || cols <= 0 || countElements <= 0)
    {
        return;
    }

    if (min > max)
    {
        int temp = min;
        min = max;
        max = temp;
    }

    std::ofstream file(fileName);
    if (!file.is_open())
    {
        return;
    }

    static bool randomInitialized = false;
    if (!randomInitialized)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        randomInitialized = true;
    }

    for (int i = 0; i < countElements; i++)
    {
        int value = min + std::rand() % (max - min + 1);
        file << value;

        if ((i + 1) % cols == 0)
        {
            file << '\n';
        }
        else if (i + 1 < countElements)
        {
            file << delimeter;
        }
    }

    if (countElements % cols != 0)
    {
        file << '\n';
    }

    file.close();
}