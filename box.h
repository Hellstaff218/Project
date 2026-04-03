#pragma once

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
};

void writeToFile(const char *fileName, const Box &box);
void readFromFile(const char *fileName, Box &box);
void readFromFile(const char *fileName, Box *box);