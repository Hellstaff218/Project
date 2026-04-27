#include "HW1.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

namespace
{
char *copyString(const std::string &text)
{
    char *result = new char[text.size() + 1];
    for (std::size_t i = 0; i < text.size(); i++)
    {
        result[i] = text[i];
    }
    result[text.size()] = '\0';
    return result;
}
}

double getTime(meas units)
{
    const auto now = std::chrono::high_resolution_clock::now().time_since_epoch();

    switch (units)
    {
    case meas::milli:
        return std::chrono::duration<double, std::milli>(now).count();
    case meas::micro:
        return std::chrono::duration<double, std::micro>(now).count();
    case meas::nano:
        return std::chrono::duration<double, std::nano>(now).count();
    case meas::pico:
        return std::chrono::duration<double, std::pico>(now).count();
    }

    return std::chrono::duration<double, std::milli>(now).count();
}

void writeStringToFile(const char *fileName, char *data)
{
    if (fileName == nullptr || data == nullptr)
    {
        return;
    }

    std::ofstream out(fileName, std::ios::app);
    if (!out.is_open())
    {
        return;
    }

    out << data;
}

char *convertDoubleToStr(double number)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << number;
    return copyString(out.str());
}

char *convertIntToStr(int number)
{
    return copyString(std::to_string(number));
}

void randomFillAr(int *ar, int size, int min, int max)
{
    if (ar == nullptr || size <= 0)
    {
        return;
    }

    if (min > max)
    {
        const int temp = min;
        min = max;
        max = temp;
    }

    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);

    for (int i = 0; i < size; i++)
    {
        ar[i] = distribution(generator);
    }
}
