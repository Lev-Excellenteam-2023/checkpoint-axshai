#include "input_handlers.h"
#include "dataBase.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MIN_GRADE_2_STAY 64

Student* parseLine(char* line, int* sClass, int* level)
{
    BOOL valid = TRUE;
    char* token;
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }
    
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        return NULL;
    }
    if (!strlen(line)) {
        valid = FALSE;
    }
    newStudent->firstName = (char*)malloc(sizeof(Student));
    token = strtok(line, " ");
    strncpy(newStudent->firstName, token, strlen(token));
    newStudent->firstName[strlen(token)] = '\0';

    newStudent->lastName = (char*)malloc(sizeof(Student));
    token = strtok(NULL, " ");
    strncpy(newStudent->lastName, token, strlen(token));
    newStudent->lastName[strlen(token)] = '\0';

    token = strtok(NULL, " ");
    newStudent->phone = atoi(token);
    if(!newStudent->phone || strlen(token) != 10)
        valid = FALSE;
    token = strtok(NULL, " ");
    *level = atoi(token);
    if (!(0 < *level && *level <= NUM_OF_LEVELS))
        valid = FALSE;
    token = strtok(NULL, " ");
    *sClass = atoi(token);
    if (!(0 < *sClass && *sClass <= NUM_OF_CLASSES))
        valid = FALSE;

    for (int i = 0; i < NUM_OF_GRADES; i++) {
        token = strtok(NULL, " ");
        newStudent->grades[i] = atoi(token);
        if (!(0 <= newStudent->grades[i] && newStudent->grades[i] <= 100))
            valid = FALSE;
    }
    if (!valid)
    {
        free(newStudent->firstName);
        free(newStudent->lastName);
        free(newStudent);
        newStudent = NULL;
    }
    return newStudent;
}

Status insertNewStudent()
{
    char line[MAX_LINE_LENGTH];
    Student* student;
    int sClass, level;
    printf("enter student deatails in this format: <first name> <last name> <phone> <level> <class> <10 grades seperated by space>\n");
    fgets(line, MAX_LINE_LENGTH, stdin);
    student = parseLine(line, &sClass, &level);
    if (student != NULL)
    {
        add(level, sClass, student);
        return Success;
    }
    else
    {
        return Fail;
    }
}

Status deleteStudent()
{
    unsigned int phone;
    BOOL isPrev;
    printf("enter the phone of the student you want to delete\n");
    scanf("%u", &phone);
    StudentNode* student2Delete = search2DeleteByPhone(phone, &isPrev);
    if (student2Delete)
    {
        if (!isPrev)
            freeStudent(student2Delete, FALSE);
        else
        {
            freeStudent(student2Delete->next, FALSE);
            student2Delete->next = NULL;

        }

        return Success;
    }
    else
    {
        printf("there is no student with phone number: 0%u\n", phone);
        return Fail;
    }
}
