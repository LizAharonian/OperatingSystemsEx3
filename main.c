/*
 * Liz Aharonian
 * 316584960
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define Fail -1
#define TRUE 1
#define FALSE 0
#define ERROR "Error in system call"
//define
#define SIZE 1
#define BULK 1
#define SPACE 32
#define A 65
#define Z 90
int isEqual(char * firstFile, char * secondFile2);

int isSimilar(char * firstFile, char * secondFile2);

void handleFailure();

char toLower(char character);

int main(int argc, char** argv) {

    if (argc!=3) {
        handleFailure();

    }

    if (isEqual(argv[1], argv[2])) {
        printf("3");
        return 3;
    } else if (isSimilar(argv[1], argv[2])) {
        printf("2");
        return 2;
    } else {
        printf("1");
        return 1;
    }
}

void handleFailure() {
    fprintf(stderr, ERROR);
    printf("\n");
    exit(Fail);
}

int isSimilar(char * firstFile, char * secondFile2) {
    //open files
    FILE *file1 = fopen(firstFile, "rb");
    if (file1 == NULL) {
        handleFailure();
    }
    FILE *file2 = fopen(secondFile2, "rb");
    if (file1 == NULL) {
        handleFailure();
    }
    char buffer1[SIZE];
    char buffer2[SIZE];
    int status;
    //read each char by buffer
    while (((status = fread(buffer1, sizeof(buffer1), BULK, file1)) != 0) &&
           ((status = fread(buffer2, sizeof(buffer2), BULK, file2)) != 0)) {
        if (status == Fail) {
            handleFailure();
        }
        //lowerCase both chars
        *buffer1 = toLower(*buffer1);
        *buffer2 = toLower(*buffer2);
        if ((*buffer1 == '\n' && *buffer2 == SPACE) ||
            (*buffer1 == SPACE && *buffer2 == '\n')) {
            continue;
        }
        //compare current chars
        if (*buffer1 != *buffer2) {
            while ((*buffer1 == SPACE || *buffer1 == '\n') &&
                   (status = fread(buffer1, sizeof(buffer1), BULK, file1)) != 0) {
                if (status == Fail) {
                    handleFailure();
                }

            }
            //lowerCase both chars
            *buffer1 = toLower(*buffer1);
            *buffer2 = toLower(*buffer2);
            if (*buffer1 != *buffer2) {
                return FALSE;
            }

            while ((*buffer2 == SPACE || *buffer2 == '\n') &&
                   (status = fread(buffer2, sizeof(buffer2), BULK, file2)) != 0) {
                if (status == Fail) {
                    handleFailure();
                }

            }
            //lowerCase both chars
            *buffer1 = toLower(*buffer1);
            *buffer2 = toLower(*buffer2);
            if (*buffer1 != *buffer2) {
                return FALSE;
            }
        }

    }
    return TRUE;
}

char toLower(char character) {
    printf("before: %c\n", character);
    if (character>=A && character<=Z) {
        character +=SPACE;
    }
    printf("after: %c\n", character);
    return character;
}

int isEqual(char * firstFile, char * secondFile2) {
    //open files
    FILE* file1 = fopen(firstFile, "rb");
    if (file1 ==NULL) {
        handleFailure();
    }
    FILE* file2 = fopen(secondFile2, "rb");
    if (file1 ==NULL) {
        handleFailure();
    }
    char buffer1[SIZE];
    char buffer2[SIZE];
    int status;
    //read each char by buffer
    while (((status = fread(buffer1, sizeof(buffer1), BULK, file1))!=0 )&&
            ((status =fread(buffer2, sizeof(buffer2), BULK, file2))!=0)) {
        if (status ==Fail) {
            handleFailure();
        }
        //compare current chars
        if (!(*buffer1==*buffer2)) {
            return FALSE;
        }

    }
    return TRUE;
}

