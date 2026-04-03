#include "box.h"

#include <fstream>

void writeToFile(const char *fileName, const Box &box)
{
    if (fileName == nullptr)
    {
        return;
    }

    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open())
    {
        return;
    }

    out.write(reinterpret_cast<const char *>(&box), sizeof(Box));
}
void readFromFile(const char *fileName, Box &box)
{
    if (fileName == nullptr)
    {
        return;
    }

    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open())
    {
        return;
    }

    in.read(reinterpret_cast<char *>(&box), sizeof(Box));
}
void readFromFile(const char *fileName, Box *box)
{
    if (fileName == nullptr || box == nullptr)
    {
        return;
    }
    readFromFile(fileName, *box);
}