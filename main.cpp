#include <iostream>

int getMax(const int* ar, int size) {
	int ind_max = 0;
	for (int i = 1; i < size; i++) {
		if (ar[ind_max] < ar[i]) {
			ind_max = i;
		}
	}
	return ind_max;
}

void selectionSort(int* ar, int size) {
	for (int i = 0; i < size; i++) {
		int indMax = getMax(ar, size - i);
		std::swap(ar[size - i - 1], ar[indMax]);
	}
}

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

int main(char argc, char** argv) {
	std::cout << (int)argc << std::endl;
	int i = 0;
	while(i < argc) {
		std::cout << i << " : " << argv[i] << std::endl;
		i++;

	}
	return 0;

	int ar[] = {1,4,2,9,0,-1,-6,10,123,5};
	showArray(ar, 10, 'g');
	selectionSort(ar, 10);
	showArray(ar, 10, 'h');


	return 0;
}
















