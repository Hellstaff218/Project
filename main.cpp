#include <iostream>

int main() {
	int array[10] = {4,7,1,9,90,23,12,89,12,-10};

	int i_max = 0;
	for (int i = 1; i < 10; i++) {
		if (array[i] > array[i_max]) {
			i_max = i;
		}
	}

	std::cout << "index = " << i_max << " val = " << array[i_max] << std::endl;




	return 0;
}
