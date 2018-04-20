/*
 * Liz Aharonian
 * 316584960
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//define
#define Fail -1
#define TRUE 1
#define FALSE 0
#define SIZE 1
#define SPACE 32
#define A 65
#define Z 90
#define ERROR "Error in system call\n"
#define STDERR 2
#define ERROR_SIZE 21

//declarations
int isEqual(char * firstFile, char * secondFile2);
int isSimilar(char * firstFile, char * secondFile2);
void handleFailure();
char toLower(char character);
char ignoreSpacesAndLines(int file, int otherFile, char bufferChar);
void createFileDescriptors(int *file1, int *file2, char* firstFile, char* secondFile );


/**
 * main function.
 * runs the program.
 * @param argc - number of command line args.
 * @param argv - command line args.
 * @return 1/2/3.
 */
int main(int argc, char **argv) {
    //validation of num of input args
    if (argc != 3) {
        handleFailure();
    }
    //classify the docs similarity
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
    write(STDERR, ERROR, ERROR_SIZE);
    exit(Fail);
}

/**
 * isSimilar function.
 * check if firstFile and secondFile looks similar.
 * @param firstFile - one of the documents to be checked.
 * @param secondFile - one of the documents to be checked.
 * @return FALSE or TRUE.
 */
int isSimilar(char *firstFile, char *secondFile) {
    //open files
    int file1;
    int file2;
    createFileDescriptors(&file1,&file2, firstFile, secondFile);
    char buffer1[SIZE];
    char buffer2[SIZE];
    int status1;
    int status2;
    //read each char by buffer
    while (1) {
        status1 = read(file1, buffer1, SIZE);
        status2 = read(file2, buffer2, SIZE);
        if (status1 == Fail || status2 == Fail) {
            close(file1);
            close(file2);
            handleFailure();
        } else if (status1 == 0 && status2 != 0) {
            //ignoreSpacesAndLines places buffer2 on char which differ from space or '\n'
            *buffer2 = ignoreSpacesAndLines(file2, file1, *buffer2);
            if (*buffer2 ==SPACE|| *buffer2=='\n') {
                break;
            }else {
                close(file1);
                close(file2);
                return FALSE;
            }
        }else if (status1 != 0 && status2 == 0) {
            //ignoreSpacesAndLines places buffer1 on char which differ from space or '\n'
            *buffer1 = ignoreSpacesAndLines(file1, file2, *buffer1);
            if (*buffer1 ==SPACE|| *buffer1=='\n') {
                break;
            }else {
                close(file1);
                close(file2);
                return FALSE;
            }

        }else if (status1 == 0 && status2 == 0) {
            break;
        } else if (*buffer1 != *buffer2) {
            //lowerCase both chars
            *buffer1 = toLower(*buffer1);
            *buffer2 = toLower(*buffer2);
            //compare current chars
            if (*buffer1 != *buffer2) {
                //ignoreSpacesAndLines places buffer1 on char which differ from space or '\n'
                *buffer1 = ignoreSpacesAndLines(file1, file2, *buffer1);
                //ignoreSpacesAndLines places buffer2 on char which differ from space or '\n'
                *buffer2 = ignoreSpacesAndLines(file2, file1, *buffer2);
                //lowerCase both chars
                *buffer1 = toLower(*buffer1);
                *buffer2 = toLower(*buffer2);
                //make the comparison again
                if (*buffer1 != *buffer2) {
                    close(file1);
                    close(file2);
                    return FALSE;
                }
            }
        }
    }
    close(file1);
    close(file2);
    return TRUE;
}

void createFileDescriptors(int *file1, int *file2, char* firstFile, char* secondFile ) {
    *file1 = open(firstFile, O_RDONLY);
    if (file1 < 0) {
        handleFailure();
    }
    *file2 = open(secondFile, O_RDONLY);
    if (file2 < 0) {
        close(*file1);
        handleFailure();
    }
}

/**
 * isEqual function.
 * checks if firstFile and secondFile looks the same.
 * @param firstFile - one of the documents to be checked.
 * @param secondFile - one of the documents to be checked.
 * @return FALSE or TRUE.
 */
int isEqual(char *firstFile, char *secondFile) {
    //open files
    int file1;
    int file2;
    createFileDescriptors(&file1,&file2, firstFile, secondFile);
    char buffer1[SIZE];
    char buffer2[SIZE];
    int status1;
    int status2;
    //read each char by buffer
    while (1) {
        status1 = read(file1, buffer1, SIZE);
        status2 = read(file2, buffer2, SIZE);
        if (status1 == Fail || status2 == Fail) {
            close(file1);
            close(file2);
            handleFailure();
        } else if ((status1 == 0 && status2 != 0) || (status1 != 0 && status2 == 0) || *buffer1 != *buffer2) {
            close(file1);
            close(file2);
            return FALSE;
        } else if (status1 == 0 && status2 == 0) {
            break;
        }
    }
    close(file1);
    close(file2);
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
char ignoreSpacesAndLines(int file, int otherFile, char bufferChar) {
    char buffer[SIZE];
    int status;
    *buffer = bufferChar;
    //while loop places buffer on char which differ from space or '\n'
    while ((*buffer == SPACE || *buffer == '\n') && (status = read(file, buffer, SIZE)) != 0) {
        if (status == Fail) {
            close(file);
            close(otherFile);
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
    if (character >= A && character <= Z) {
        character += SPACE;
    }
    return character;
}


