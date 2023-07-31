

#include "school.h"
#include "dataBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LENGTH 100

int main() {
    FILE* file = fopen("students_with_class.txt", "r");
    if (!file) {
        printf("Error opening the file.\n");
        return 1;
    }
    initDataBase(file);
    fclose(file);
    printDataBase();
    clearDataBase();

    
}
