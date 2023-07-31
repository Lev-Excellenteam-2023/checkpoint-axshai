#ifndef DATA_BASE_H
#define DATA_BASE_H
#include "school.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct studentNode {
	Student* student;
	struct studentNode* next;
} StudentNode;




//extern StudentNode* g_schooldDataBase[NUM_OF_LEVELS][NUM_OF_CLASSES];
void initDataBase(FILE* file);
void push(StudentNode * *head, Student * newStudent);
void printDataBase();
void clearDataBase();
#endif
