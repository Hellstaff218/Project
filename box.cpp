#include "box.h"
#include <cstdio>



Box::Box() : len(10), width(10), height(10) {
    calculateVolume();
}

Box::Box(int value) : len(value), width(value), height(value) {
    calculateVolume();
}

Box::Box(int len, int width, int height) : len(len), width(width), height(height) {
    calculateVolume();
}

void Box::calculateVolume() {
    volume = len * width * height;
}



std::ostream& operator<<(std::ostream& os, const Box& box) {
    os << "len = " << box.len
        << ", width = " << box.width
        << ", height = " << box.height
        << ", volume = " << box.volume << "\n";
    return os;
}

 

void writeToFile(const char* fileName, const struct Box& box) {
    FILE* file = nullptr;
    if (fopen_s(&file, fileName, "wb") == 0 && file != nullptr) {
        fwrite(&box, sizeof(Box), 1, file);
        fclose(file);
    }
}

void readFromFile(const char* fileName, struct Box* box) {
    if (fileName == nullptr || box == nullptr) {
        return; 
    }
    FILE* file = nullptr;
    if (fopen_s(&file, fileName, "rb") == 0 && file != nullptr) {
        fread(box, sizeof(Box), 1, file);
        fclose(file);
    }
}