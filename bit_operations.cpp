#include "bit_operations.h"


void swapHalfWord(unsigned int* words) {
unsigned int temp = *words;
temp = temp>>16;
*words=*words<<16;
*words=*words|temp;
}

void cycleShift(int* number, int N, int left) {
	N%=32;
bool ok =false;
if (left==1) ok=true;
int temp = *number;
temp= (ok)? (temp>>32-N) : (temp<<32-N);
*number= (ok)? (*number<<N) : (*number>>N);
*number=  temp|*number;
}

int getMaxBit(const int* array, int N) {
	if (N <= 0) return -1; 
	int count_max=-1;
	int ind_max =-1;
	for (int i=0;i<N;i++) {
		if (array[i]<0)
			continue;
		int x=array[i];
		int count = 0;
		
		while (x!=0) {
			count = count + (x&1);
			x=x>>1;
		}
		if (count>count_max){ 
		 count_max=count;
		 ind_max = i;	
	}
	}
	return ind_max;
}

unsigned char getCount1Bit(int number) {
int count=0;
unsigned int x=number;
	while (x!=0) {
		count = count + (x&1);
		x=x>>1;
} 
return count;
}

void cycleShiftArray(int* array, int size, int N, bool left)  {
	N = N % 32;
if (N == 0 || size <= 0) return;
bool ok = true;
if (left==0) ok = false;
unsigned int temp1 = ok? (array[0]>>(32-N)): (array[size-1]<<(32-N));
	if (ok) {
		for (int i = 0; i < size - 1; i++) {
		unsigned int temp2 = array[i + 1] >> (32 - N);
		array[i] = (array[i] << N) | temp2;
		}
	array[size - 1] = (array[size - 1] << N) | temp1;
	}
	else {
		for (int i =size-1; i>0;i--) {
		unsigned int temp2 = array[i-1]<<(32-N);
		array[i]=(array[i]>>N) | temp2;
		}
	array[0]=(array[0]>>N) | temp1;
	}
}

void setBit(int* number, int numBit) { 
int bit = 1;
	bit =bit << numBit;

 *number = *number | bit;


}

void clearBit(int* number, int numBit) {
	int bit =1;
	bit=bit << numBit;
	*number=*number &(~bit);
}
