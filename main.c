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
int isEqual(FILE* file1, FILE* file2);

int isSimilar(FILE* file1, FILE* file2);

void handleFailure();

int main(int argc, char** argv) {

    if (argc!=2) {
        handleFailure();

    }
    //open files
    FILE* file1 = fopen(argv[1], "rb");
    FILE* file2 = fopen(argv[2], "rb");
    if (file1 ==NULL||file2==NULL) {
        handleFailure();
    }
    if (isEqual(file1, file2)) {
        return 3;
    } else if (isSimilar(file1, file2)) {
        return 2;
    } else {
        return 1;
    }
}

void handleFailure() {
    fprintf(stderr, ERROR);
    printf("\n");
    exit(Fail);
}

int isSimilar(FILE* file1, FILE* file2) {

}

int isEqual(FILE* file1, FILE* file2) {

}

