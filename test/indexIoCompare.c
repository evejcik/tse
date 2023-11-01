/* 
 * indexIoCompare.c --- 
 * 
 * Author: Matthew J. Sebastian
 * Created: 10-31-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int compareFiles(FILE *file1, FILE *file2) {
    char ch1, ch2;

    do {
        ch1 = fgetc(file1);
        ch2 = fgetc(file2);

        if (ch1 != ch2) {
            return 0; 
        }
    } while (ch1 != EOF && ch2 != EOF);

    return (ch1 == EOF && ch2 == EOF);
}

int main() {
	FILE *file1;
	FILE *file2;
    char file1Name[] = "indexSaveTest";
    char file2Name[] = "indexSaveTest1";

    file1 = fopen(file1Name, "r");
    file2 = fopen(file2Name, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        return 1;
    }

    if (compareFiles(file1, file2)) {
        printf("Files are the same.\n");
    } else {
        printf("Files are different.\n");
    }

    fclose(file1);
    fclose(file2);

    return 0;
}
