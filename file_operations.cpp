#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillFile(const char* fileName, int min, int max, char delimiter, int cols, int countElements) {
    FILE* file = fopen(fileName, "w");

    if (!file) {
        return ;
    }

    for (int i = 0; i < countElements; i++) {
        int num = min + rand() % (max - min + 1);
        fprintf(file, "%d", num);
        if (i != countElements - 1) {
            fprintf(file, "%c", delimiter);
        }

       
        if ((i + 1) % cols == 0) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
}
