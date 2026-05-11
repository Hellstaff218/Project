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
