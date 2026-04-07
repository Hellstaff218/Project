#include "box.h"

#include <fstream>

Box::Box()
{
    _len = 10;
    _width = 10;
    _height = 10;
    _color = 0;
    updateVolume();
}

Box::Box(int value)
{
    _len = value;
    _width = value;
    _height = value;
    _color = 0;
    updateVolume();
}

Box::Box(int len, int width, int height)
{
    _len = len;
    _width = width;
    _height = height;
    _color = 0;
    updateVolume();
}

void Box::updateVolume()
{
    volume = _len * _width * _height;
}

std::ostream &operator<<(std::ostream &out, const Box &box)
{
    out << std::dec
        << "len = " << box._len
        << ", width = " << box._width
        << ", height = " << box._height
        << ", volume = " << box.volume << '\n';
    return out;
}

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
    box.updateVolume();
}
void readFromFile(const char *fileName, Box *box)
{
    if (fileName == nullptr || box == nullptr)
    {
        return;
    }
    readFromFile(fileName, *box);
}
