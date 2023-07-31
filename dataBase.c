#include "dataBase.h"
#include "school.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LENGTH 150
StudentNode* g_schooldDataBase[NUM_OF_LEVELS][NUM_OF_CLASSES];
static Student* _parseLine(char* line, int* sClass, int* level)
{
    char* token;
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        return NULL;
    }
    newStudent->firstName = (char*)malloc(sizeof(Student));
    token = strtok(line, " ");
    strncpy(newStudent->firstName, token, sizeof(token) - 1);
    newStudent->firstName[sizeof(newStudent->firstName) - 1] = '\0';

    newStudent->lastName = (char*)malloc(sizeof(Student));
    token = strtok(NULL, " ");
    strncpy(newStudent->lastName, token, sizeof(token) - 1);
    newStudent->lastName[sizeof(newStudent->lastName) - 1] = '\0';

    token = strtok(NULL, " ");
    newStudent->phone = atoi(token);

    token = strtok(NULL, " ");
    *level = atoi(token);
    
    token = strtok(NULL, " ");
    *sClass = atoi(token);


    for (int i = 0; i < NUM_OF_GRADES; i++) {
        token = strtok(NULL, " ");
        newStudent->grades[i] = atoi(token);
    }
    return newStudent;
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
        student = _parseLine(line, &sClass, &level);
        if (student != NULL) 
        {
            push(&g_schooldDataBase[level -1][sClass - 1], student);
        }
    }

}

void push(StudentNode** head, Student* newStudent) 
{
	StudentNode* newNode;
	newNode = (StudentNode*)malloc(sizeof(StudentNode));

	newNode->student = newStudent;
	newNode->next = *head;
	*head = newNode;

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

void clearDataBase()
{

    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            StudentNode* current = g_schooldDataBase[sLevel][sClass];
            while (current != NULL) {
                StudentNode* temp = current;
                current = current->next;
                free(temp->student->firstName);
                free(temp->student->lastName);
                free(temp->student);
                free(temp);

            }
        }
    }
}
