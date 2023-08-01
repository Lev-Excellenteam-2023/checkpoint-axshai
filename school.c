#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "school.h"
#define _CRT_SECURE_NO_WARNINGS
void printStudent(Student* student, FILE * f)
{
    fprintf(f, "name: %s %s ,phone: 0%d ", student->firstName, student->lastName, student->phone);
    for (int i = 0; i < NUM_OF_GRADES; ++i) {
        fprintf(f, "%d ", student->grades[i]);
    }
    fprintf(f, "\n");
}

double calcStudentAverage(Student* student)
{
    int sum = 0;
    for (int i = 0; i < NUM_OF_GRADES; i++)
    {
        sum += student->grades[i];
    }
    return ((double)sum) / NUM_OF_GRADES;
}
