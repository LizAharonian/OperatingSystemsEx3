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
char ignoreSpacesAndLines(FILE* file, FILE* otherFile, char bufferChar);

/**
 * main function.
 * runs the program.
 * @param argc - number of command line args.
 * @param argv - command line args.
 * @return 1/2/3.
 */
int main(int argc, char** argv) {
    //validation on num of input args
    if (argc!=3) {
        handleFailure();
    }
    //classify the docs
    if (isEqual(argv[1], argv[2])) {
        return 3;
    } else if (isSimilar(argv[1], argv[2])) {
        return 2;
    } else {
        return 1;
    }
}

/**
 * handleFailure function.
 * prints error and exits the program.
 */
void handleFailure() {
    fprintf(stderr, ERROR);
    printf("\n");
    exit(Fail);
}
/**
 * isSimilar function.
 * check if firstFile and secondFile looks similar.
 * @param firstFile - one of the documents to be checked.
 * @param secondFile - one of the documents to be checked.
 * @return FALSE or TRUE.
 */
int isSimilar(char * firstFile, char * secondFile) {
    //open files
    FILE *file1 = fopen(firstFile, "rb");
    if (file1 == NULL) {
        handleFailure();
    }
    FILE *file2 = fopen(secondFile, "rb");
    if (file2 == NULL) {
        fclose(file1);
        handleFailure();
    }
    char buffer1[SIZE];
    char buffer2[SIZE];
    int status;
    //read each char by the buffer
    while (((status = fread(buffer1, sizeof(buffer1), BULK, file1)) != 0) &&
           ((status = fread(buffer2, sizeof(buffer2), BULK, file2)) != 0)) {
        if (status == Fail) {
            handleFailure();
        }
        //lowerCase both chars
        *buffer1 = toLower(*buffer1);
        *buffer2 = toLower(*buffer2);
        //compare current chars
        if (*buffer1 != *buffer2) {
            //ignoreSpacesAndLines places buffer1 on char which differ from space or '\n'
            *buffer1 = ignoreSpacesAndLines(file1,file2,*buffer1);
            //ignoreSpacesAndLines places buffer2 on char which differ from space or '\n'
            *buffer2 = ignoreSpacesAndLines(file2,file1,*buffer2);
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

/**
 * isEqual function.
 * checks if firstFile and secondFile looks the same.
 * @param firstFile - one of the documents to be checked.
 * @param secondFile - one of the documents to be checked.
 * @return FALSE or TRUE.
 */
int isEqual(char * firstFile, char * secondFile) {
    //open files
    FILE* file1 = fopen(firstFile, "rb");
    if (file1 ==NULL) {
        handleFailure();
    }
    FILE* file2 = fopen(secondFile, "rb");
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

/**
 * ignoreSpacesAndLines function.
 * the function places bufferChar on char which differ from space or '\n'.
 * @param file - file stream.
 * @param otherFile - other fileStream.
 * @param bufferChar - current buffer content.
 * @return new val of buffer.
 */
char ignoreSpacesAndLines(FILE* file, FILE* otherFile, char bufferChar) {
    char buffer[SIZE];
    int status;
    *buffer=bufferChar;
    //while loop places buffer on char which differ from space or '\n'
    while ((*buffer == SPACE || *buffer == '\n') &&
           (status = fread(buffer, sizeof(buffer), BULK, file)) != 0) {
        if (status == Fail) {
            fclose(file);
            fclose(otherFile);
            handleFailure();
        }
    }
    return *buffer;
}

/**
 * toLower function.
 * @param character - char to be lowercase.
 * @return the lowercase char.
 */
char toLower(char character) {
    if (character>=A && character<=Z) {
        character +=SPACE;
    }
    return character;
}
