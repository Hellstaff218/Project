#ifndef _HW1_h_
#define _HW1_h_

enum class meas
{
    milli = 1,
    micro = 2,
    nano = 3,
    pico = 4
};

double getTime(meas units);
void writeStringToFile(const char *fileName, char *data);
char *convertDoubleToStr(double number);
char *convertIntToStr(int number);
void randomFillAr(int *ar, int size, int min = -100, int max = 100);

#endif
