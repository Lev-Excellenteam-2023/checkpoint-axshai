#include "dataBase.h"
#include "input_handlers.h"
#include "school.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

StudentNode* g_schooldDataBase[NUM_OF_LEVELS][NUM_OF_CLASSES];

static int _findIndexOfMin(StudentNode **arr, int n, int courseNum) {
    StudentNode* min = arr[0];
    int minIndex = 0;

    for (int i = 1; i < n && arr[n]; i++) {
        if (arr[i] ->student->grades[courseNum] < min -> student->grades[courseNum]) {
            min = arr[i];
            minIndex = i;
        }
    }

    return minIndex;
}

static void _push(StudentNode** head, Student* newStudent)
{
    StudentNode* newNode;
    newNode = (StudentNode*)malloc(sizeof(StudentNode));

    newNode->student = newStudent;
    newNode->next = *head;
    *head = newNode;

}

static void _printClass(StudentNode* sClass, FILE* f)
{
    StudentNode* current = sClass;
    while (current != NULL) 
    {
        printStudent(current->student, f);
        current = current->next;
    }
}

void initDataBase(FILE* file)
{
    Student* student;
    int sClass, level;
    char line[MAX_LINE_LENGTH];
    int num = 0;
  
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        num++;
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

void printDataBase(FILE* f)
{
    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            if (g_schooldDataBase[sLevel][sClass] != NULL)
            {
                _printClass(g_schooldDataBase[sLevel][sClass], f);
            }
        }
    }
}
 
void freeStudent(StudentNode* student2delete, BOOL all)
{
    StudentNode* temp = student2delete->next;
   // printf("realese: %s\n", student2delete->student->firstName);
    free(student2delete->student->firstName);
    free(student2delete->student->lastName);
    free(student2delete->student);
    free(student2delete);
    if (!all && temp)
        *student2delete = *(temp);
    
}

double calcLevelAverage(int level, int course)
{
    int numOfStudents = 0;
    int sumOfGrades = 0;
    for (int cls = 0; cls < NUM_OF_CLASSES; cls++)
    {
        StudentNode* head = g_schooldDataBase[level][cls];
        while (head != NULL)
        {
            sumOfGrades += head->student->grades[course];
            numOfStudents++;
            head = head->next;
        }
    }
    return !numOfStudents? 0:((double)sumOfGrades) / numOfStudents;
}

void getStudentUnderGrade(int minGrade, StudentNode** container)
{
    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            StudentNode* head = g_schooldDataBase[sLevel][sClass];
            while (head != NULL)
            {
                if (head != NULL && (calcStudentAverage(head->student) < minGrade))
                {
                    _push(container, head->student);
                }
                head = head->next;
            }
        }
    }
}

void findTopN(StudentNode** arr, int n, int level, int courseNum)
{
    int arrIndex = 0;
    int minStudentIndex;
    for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
    {
        StudentNode* head = g_schooldDataBase[level][sClass];
        while (head != NULL)
        {
            if (arr[arrIndex] == NULL && arrIndex < n)
            {
                arr[arrIndex] = head;
                arrIndex++;
            }
            else
            {
                minStudentIndex = _findIndexOfMin(arr, n, courseNum);
                if (arr[minStudentIndex]->student->grades[courseNum] < head->student->grades[courseNum])
                {
                    arr[minStudentIndex] = head;
                }
            }
            head = head->next;
        }
        
    }
}

void clearDataBase()
{

    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            printf("relase now %d %d\n", sLevel, sClass);
            StudentNode* current = g_schooldDataBase[sLevel][sClass];
            while (current != NULL) {
                StudentNode* student2delete = current;
                current = current->next;
                freeStudent(student2delete, TRUE);

            }
        }
    }
}

StudentNode* search2DeleteByPhone(unsigned int phone, BOOL *isLast)
{
    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            if (g_schooldDataBase[sLevel][sClass] != NULL && g_schooldDataBase[sLevel][sClass]->student->phone == phone)
            {
                *isLast = FALSE;
                StudentNode* temp = g_schooldDataBase[sLevel][sClass];
                g_schooldDataBase[sLevel][sClass] = NULL;
                return temp;
            }
            StudentNode* head = g_schooldDataBase[sLevel][sClass];
            while (head != NULL)
            {
                if (head->next != NULL && head->next->student->phone == phone)
                {
                    if (head->next->next == NULL)
                    {
                        *isLast = TRUE;
                        return head;
                    }
                    else
                    {
                        *isLast = FALSE;
                        return head->next;
                    }

                }
                head = head->next;
            }
        }
    }
    return NULL;
}

StudentNode* searchByPhone(unsigned int phone)
{
    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            StudentNode* head = g_schooldDataBase[sLevel][sClass];
            while (head != NULL)
            {
                if (head != NULL && head->student->phone == phone)
                {
                    return head;

                }
                head = head->next;
            }
        }
    }
    return NULL;
}

StudentNode* searchByName(char* fName, char* lName, int* level, int* stClass)
{
    for (int sLevel = 0; sLevel < NUM_OF_LEVELS; sLevel++)
    {
        for (int sClass = 0; sClass < NUM_OF_CLASSES; sClass++)
        {
            StudentNode* head = g_schooldDataBase[sLevel][sClass];
            while (head != NULL)
            {
                if (strcmp(head->student->lastName, lName) == 0 && strcmp(head->student->firstName, fName) == 0)
                {
                    *level = sLevel;
                    *stClass = sClass;
                    return head;

                }
                head = head->next;
            }

            
        }
    }
    return NULL;
}
