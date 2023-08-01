#include "school.h"
#include "dataBase.h"
#include "input_handlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LENGTH 100
void menu();
int main() {
    FILE* file = fopen("students_with_class.txt", "r");
    if (!file) {
        printf("Error opening the file.\n");
        return 1;
    }
    initDataBase(file);
    fclose(file);
//    printDataBase();
    menu();
//    clearDataBase();
//    printDataBase();
    return 0;

    
}


enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};

void menu() {
    char input;
    // school.name = "schoolName";
    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
        case Insert:
            insertNewStudent();
            break;
            
        case Delete:
            deleteStudent();
            break;
        case Edit:
            editStudentGrade();
            break;
            
        case Search:
            searchStudent();
            
            break;
        case Showall:
            printAllStudents();
            break;
        case Top10:
            printTopNStudentsPerCourse();
            break;
            
        case UnderperformedStudents:
            printUnderperformedStudents();
            break;
            
        case Average:
            printAverage();
            break;
        case Export:
            exportDatabase();
            break;
        case Exit:
            handleClosing();
            break;
            
        default:
            printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                input);
            getc(stdin);
            getc(stdin);
            break;
        }
    } while (input != Exit);
}


