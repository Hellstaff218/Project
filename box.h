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
    // уникальный номер объекта
    int _boxNumber;
    // объем
    int volume;
    // флаг отрицательного объема
    bool _hasNegativeVolume;

    Box();
    Box(int value);
    Box(int len, int width, int height);
    Box(const Box &other);
    Box &operator=(const Box &other);
    ~Box();

    void updateVolume();
};

std::ostream &operator<<(std::ostream &out, const Box &box);
void printBoxNumberState(std::ostream &out);

void writeToFile(const char *fileName, const Box &box);
void readFromFile(const char *fileName, Box &box);
void readFromFile(const char *fileName, Box *box);
