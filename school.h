#ifndef SCHOOL_H
#define SCHOOL_H
#define _CRT_SECURE_NO_WARNINGS
#define NUM_OF_LEVELS 12
#define NUM_OF_CLASSES 10
#define NUM_OF_GRADES 10

typedef struct {
    char* firstName;
    char* lastName;
    unsigned int phone;
    int grades[NUM_OF_GRADES];
} Student;


#endif