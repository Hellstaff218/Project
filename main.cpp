#include <iostream>


int getMax(const int* array, int size) {
	int i_max = 0;
	for (int i = 1; i < size; i++) {
		if (array[i] > array[i_max]) {
			i_max = i;
		}
	}

	return i_max;
}

int main() {
	int array[10] = {4,7,1,9,90,23,12,89,12,-10};


	int i_max = getMax(array, 10);
	std::cout << "index = " << getMax(&array[0], 10)  << " val = " << array[i_max] << std::endl;




	return 0;
}
