/*
 * Liz Aharonian
 * 316584960
 */
#include <stdio.h>
#include <stdlib.h>
//define
#define Fail -1
#define TRUE 1
#define FALSE 0
#define SIZE 1
#define BULK 1
#define SPACE 32
#define A 65
#define Z 90
#define ERROR "Error in system call"

//declarations
int isEqual(char * firstFile, char * secondFile2);
int isSimilar(char * firstFile, char * secondFile2);
void handleFailure();
char toLower(char character);


FILE *createFileStream(char *file);

int main(int argc, char** argv) {
    //validation on num of input args
    if (argc!=3) {
        handleFailure();
    }
    //classify the docs
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
    if (file2 == NULL) {
        fclose(file1);
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
            //while loop places buffer1 on char which differ from space or '\n'
            while ((*buffer1 == SPACE || *buffer1 == '\n') &&
                   (status = fread(buffer1, sizeof(buffer1), BULK, file1)) != 0) {
                if (status == Fail) {
                    fclose(file1);
                    fclose(file2);
                    handleFailure();

                }

            }
            //while loop places buffer2 on char which differ from space or '\n'
            while ((*buffer2 == SPACE || *buffer2 == '\n') &&
                   (status = fread(buffer2, sizeof(buffer2), BULK, file2)) != 0) {
                if (status == Fail) {
                    fclose(file1);
                    fclose(file2);
                    handleFailure();
                }

            }
            //lowerCase both chars
            *buffer1 = toLower(*buffer1);
            *buffer2 = toLower(*buffer2);
            //make the comparison again
            if (*buffer1 != *buffer2) {
                fclose(file1);
                fclose(file2);
                return FALSE;
            }
        }

    }
    fclose(file1);
    fclose(file2);
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
   // FILE* file1 = createFileStream(firstFile);
    FILE* file1 = fopen(firstFile, "rb");
    if (file1 ==NULL) {
        handleFailure();
    }
    FILE* file2 = fopen(secondFile2, "rb");
    if (file2 ==NULL) {

        fclose(file1);

        handleFailure();
    }
    char buffer1[SIZE];
    char buffer2[SIZE];
    int status;
    //read each char by buffer
    while (((status = fread(buffer1, sizeof(buffer1), BULK, file1))!=0 )&&
            ((status =fread(buffer2, sizeof(buffer2), BULK, file2))!=0)) {
        if (status ==Fail) {
            fclose(file1);
            fclose(file2);
            handleFailure();
        }
        //compare current chars
        if (*buffer1!=*buffer2) {
            fclose(file1);
            fclose(file2);
            return FALSE;
        }

    }
    fclose(file1);
    fclose(file2);
    return TRUE;
}

/*FILE *createFileStream(char *file) {
    FILE* fileStream = fopen(file, "rb");
    if (fileStream ==NULL) {
        handleFailure();
    }
}*/

