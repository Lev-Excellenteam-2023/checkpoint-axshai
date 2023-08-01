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
void printDataBase();
void clearDataBase();
void add(int level, int sClass, Student* student);
void freeStudent(StudentNode* student2delete);
#endif
