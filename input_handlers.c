#include "input_handlers.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Student* parseLine(char* line, int* sClass, int* level)
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