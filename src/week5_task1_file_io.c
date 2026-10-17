// week5_task1_file_io.c
// Name: Şükrü Bedirhan  Surname: Hocuk  Student ID: 251ADB011
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task1_file_io

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    const char *filename = DEFAULT_FILENAME;
    char line[LINE_LEN];
    int line_count = 0;

    // Use the file name from the command line if one is given
    if (argc > 1) {
        filename = argv[1];
    }

    // Open the file for writing ("w" creates it or clears it)
    printf("Writing lines to %s...\n", filename);
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // Write two lines and close the file so the data is saved
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fclose(fp);

    // Open the same file again, this time for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // Read one line at a time until the end of the file
    printf("Reading contents:\n");
    while (fgets(line, sizeof line, fp) != NULL) {
        printf("%s", line);
        line_count++;
    }
    fclose(fp);

    printf("Lines read: %d\n", line_count);

    return EXIT_SUCCESS;
}
