#include "box.h"

#include <fstream>
#include <limits>
#include <set>

namespace
{
std::set<int> liveBoxNumbers;

int acquireBoxNumber()
{
    if (liveBoxNumbers.empty())
    {
        liveBoxNumbers.insert(1);
        return 1;
    }

    const int boxNumber = *liveBoxNumbers.rbegin() + 1;
    liveBoxNumbers.insert(boxNumber);
    return boxNumber;
}

int getNextBoxNumberCandidate()
{
    if (liveBoxNumbers.empty())
    {
        return 1;
    }

    return *liveBoxNumbers.rbegin() + 1;
}

void releaseBoxNumber(int boxNumber)
{
    if (boxNumber > 0)
    {
        liveBoxNumbers.erase(boxNumber);
    }
}

struct BoxFileData
{
    int len;
    int width;
    int height;
    int color;
};
}

Box::Box()
{
    _len = 10;
    _width = 10;
    _height = 10;
    _color = 0;
    _boxNumber = acquireBoxNumber();
    updateVolume();
}

Box::Box(int value)
{
    _len = value;
    _width = value;
    _height = value;
    _color = 0;
    _boxNumber = acquireBoxNumber();
    updateVolume();
}

Box::Box(int len, int width, int height)
{
    _len = len;
    _width = width;
    _height = height;
    _color = 0;
    _boxNumber = acquireBoxNumber();
    updateVolume();
}

Box::Box(const Box &other)
{
    _len = other._len;
    _width = other._width;
    _height = other._height;
    _color = other._color;
    _boxNumber = acquireBoxNumber();
    updateVolume();
}

Box &Box::operator=(const Box &other)
{
    if (this == &other)
    {
        return *this;
    }

    _len = other._len;
    _width = other._width;
    _height = other._height;
    _color = other._color;
    updateVolume();
    return *this;
}

Box::~Box()
{
    releaseBoxNumber(_boxNumber);
}

void Box::updateVolume()
{
    const long long calculatedVolume =
        static_cast<long long>(_len) * _width * _height;

    _hasNegativeVolume = calculatedVolume < 0;
    if (_hasNegativeVolume)
    {
        volume = 0;
        return;
    }

    if (calculatedVolume > std::numeric_limits<int>::max())
    {
        volume = std::numeric_limits<int>::max();
        return;
    }

    volume = static_cast<int>(calculatedVolume);
}

std::ostream &operator<<(std::ostream &out, const Box &box)
{
    out << std::dec
        << "[" << box._boxNumber << "] = {"
        << box._len << ", " << box._width << ", " << box._height << "} = ";

    if (box._hasNegativeVolume)
    {
        out << "v < 0\n";
    }
    else
    {
        out << box.volume << '\n';
    }

    return out;
}

void printBoxNumberState(std::ostream &out)
{
    out << "Активные номера: [";

    bool isFirst = true;
    for (const int boxNumber : liveBoxNumbers)
    {
        if (!isFirst)
        {
            out << ", ";
        }

        out << boxNumber;
        isFirst = false;
    }

    out << "]";
    out << ", следующий номер: " << getNextBoxNumberCandidate() << '\n';
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

    const BoxFileData data = {box._len, box._width, box._height, box._color};
    out.write(reinterpret_cast<const char *>(&data), sizeof(data));
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

    BoxFileData data = {};
    in.read(reinterpret_cast<char *>(&data), sizeof(data));
    if (!in)
    {
        return;
    }

    box._len = data.len;
    box._width = data.width;
    box._height = data.height;
    box._color = data.color;
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
