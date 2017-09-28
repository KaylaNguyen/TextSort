#include <stdio.h>   /* For fprintf, stderr, perror, stdout */
#include <stdlib.h>  /* For exit, waitpid, WEXITSTATUS */
#include <string.h>

int indexToSort = 0;

// Separate words by space in an array.
void getWords(const char *string, char wordArray[10][20]) {
    // TODO: handle multiple space between words.
    // TODO: handle key does not exist on line.
    // TODO: handle empty line.
    int n = 0;
    int j = 0;

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] != ' ') {
            wordArray[n][j++] = string[i];
        } else {
            wordArray[n][j++] = '\0';
            n++;
            j = 0;
        }
    }
}

int compareFunc(const void *a, const void *b) {
//    printf("IN COMPARE: %s\n", a);
//    printf("IN COMPARE: %s\n", b);
    char arrA[10][20];
    char arrB[10][20];
    getWords(a, arrA);
    getWords(b, arrB);
//    for(int i=0; i <= aLength;i++)
//        printf("%s\n", arrA[i]);
//    printf("Comparing %s and %s", arrA[indexToSort], arrB[indexToSort]);
    return strcmp(arrA[indexToSort], arrB[indexToSort]);

//    const char* aa = (const char*)a;
//    const char* bb = (const char*)b;

    return strcmp(a, b);
}

int main(int argc, char *argv[]) {
    // TODO: make sure every error encountered main returns code 1.
    // Process user's input.
    char *fileName;
//    int indexToSort = 0;

    if (argc > 3 | argc < 2) {
        // TODO: fix these print to stderr instead.
        printf("%s", "Invalid number of arguments.\n");
        printf("%s", "Usage: ./textsort [word index to sort] [file name] or ./textsort [file name]\n");
        return 1;
    } else if (argc == 2) {
        fileName = argv[1];
    } else {
        fileName = argv[2];
//        printf("%c", argv[1][0]);
        if (argv[1][0] != '-') {
            printf("%s", "Usage: ./textsort [word index to sort] [file name]\n");
            return -1;
        }
//        memmove(argv[1], argv[1]+1, strlen(argv[1]));
        char *pointerToIndex = argv[1];
        pointerToIndex++;
//        printf("%c", *pointerToIndex);
        indexToSort = *pointerToIndex - '0' - 1;
    }

    printf("%s\n", fileName);
    printf("%d\n", indexToSort);

    // Open file and read from file.
    FILE *file;
    // TODO: handle line longer than 128.
    int lineSize = 128;
    char stringBuffer[lineSize];

    // Create an array to store lines read from file.
//    size_t arraySize = 1;
    // TODO: figure out the true file length.
    int arraySize = 100;
//    char* stringArray = malloc(arraySize * sizeof(char));
    char stringArray[arraySize][lineSize];
    int elementNum = 0;

    file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s.\n", fileName);
        return 1;
    }
    while (fgets(stringBuffer, lineSize, file) != NULL) {
        strcpy(stringArray[elementNum], stringBuffer);
//            stringArray[elementNum] = stringBuffer;
        elementNum++;
//            printf("%d", elementNum);
//        for (int i = 0; i < arraySize; i++) {
//            printf("%s", stringArray[i]);
//        }

//            if (elementNum == arraySize){
//                arraySize *= 2;
//                char* newArray = realloc(stringArray, arraySize * sizeof(char));
//                if (newArray){
//                    stringArray = newArray;
//                }
//                else {
//                    perror("Failed allocating memory.");
//                    exit(-1);
//                }
//            }
//            printf("1 : %s\n", stringBuffer);
    }

    qsort(stringArray, elementNum, lineSize, compareFunc);

    printf("%s", "\n");
    for (int i = 0; i < elementNum; i++) {
        printf("%s", stringArray[i]);
        printf("%s", "\n");
    }
    fclose(file);


    return 0;
}
