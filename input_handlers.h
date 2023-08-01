#ifndef INPUT_HANDLERS_H
#define INPUT_HANDLERS_H
#include "school.h"

#define MAX_LINE_LENGTH 150
#define MAX_FNAME_LENGTH 25
#define MAX_LNAME_LENGTH 25
typedef enum Status_E { Success , Fail} Status;
Student* parseLine(char* line, int* sClass, int* level);
#endif