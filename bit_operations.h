#ifndef _bit_operations_h_
#define _bit_operations_h_


void swapHalfWord(unsigned int* words); 
void cycleShift(int* number, int N, int left); 
int getMaxBit(const int* array, int N); 
unsigned char getCount1Bit(int number);
void cycleShiftArray(int* array, int size, int N, bool left);
void setBit(int* number, int numBit);
void clearBit(int* number, int numBit);

#endif
