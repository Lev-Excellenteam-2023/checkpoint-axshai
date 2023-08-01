#include "dataBase.h"
#include "input_handlers.h"
#include "school.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LENGTH 150
StudentNode* g_schooldDataBase[NUM_OF_LEVELS][NUM_OF_CLASSES];

static void _push(StudentNode** head, Student* newStudent)
{
    StudentNode* newNode;
    newNode = (StudentNode*)malloc(sizeof(StudentNode));

    newNode->student = newStudent;
    newNode->next = *head;
    *head = newNode;

}


static void _printStudent(Student* student)
{
    printf("name: %s %s ,phone: 0%d ", student->firstName, student->lastName, student->phone);
    for (int i = 0; i < NUM_OF_GRADES; ++i) {
        printf("%d ", student->grades[i]);
    }
    printf("\n");

}

static void _printClass(StudentNode* sClass)
{
    StudentNode* current = sClass;
    while (current != NULL) 
    {
        _printStudent(current->student);
        current = current->next;
    }
}

void initDataBase(FILE* file)
{
	g_schooldDataBase[0][0] = NULL;
    Student* student;
    int sClass, level;
    char line[MAX_LINE_LENGTH];

  
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        student = parseLine(line, &sClass, &level);
        if (student != NULL) 
        {
            add(level, sClass, student);
        }
    }

}

void add(int level, int sClass, Student* student)
{
    _push(&g_schooldDataBase[level - 1][sClass - 1], student);
}

void printDataBase()
{
    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            if (g_schooldDataBase[sLevel][sClass] != NULL)
            {
                _printClass(g_schooldDataBase[sLevel][sClass]);
            }
        }
    }
}
 
void freeStudent(StudentNode* student2delete)
{
    StudentNode* temp = student2delete;
    student2delete = student2delete->next;
    free(temp->student->firstName);
    free(temp->student->lastName);
    free(temp->student);
    free(temp);

}

void clearDataBase()
{

    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            StudentNode* current = g_schooldDataBase[sLevel][sClass];
            while (current != NULL) {
                StudentNode* student2delete = current;
                current = current->next;
                freeStudent(student2delete);

            }
        }
    }
}

