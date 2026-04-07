#pragma once

#include <ostream>

struct Box
{
    // длина
    int _len;
    // ширина
    int _width;
    // высота
    int _height;
    // цвет
    int _color;
    // объем
    int volume;

    Box();
    Box(int value);
    Box(int len, int width, int height);

    void updateVolume();
};

std::ostream &operator<<(std::ostream &out, const Box &box);

void writeToFile(const char *fileName, const Box &box);
void readFromFile(const char *fileName, Box &box);
void readFromFile(const char *fileName, Box *box);
