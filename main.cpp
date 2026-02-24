#include <iostream>

#include "sorts.h"



void showArray(const int* ar, int size, char format) {
	switch(format) {
		case 'H' :
		case 'h' :
			std::cout << std::hex;
			break;
		case 'D' :
		case 'd' :
			std::cout << std::dec;
			break;
		default :
			std::cout << "unknown format for out, set default as decimal" << std::endl;
			std::cout << std::dec;
			break;
	}
	
	for(int i = 0; i < size; i++) {
		std::cout << ar[i] << " ";
	}
	std::cout << std::dec << std::endl;
}

int main(int argc, char** argv) {

	int ar[10] = {-12,16,1,24,5,6,4,12,9,8};
	getMax(ar, 10);

	selectionSort(ar, 10);

	return 0;
}
















