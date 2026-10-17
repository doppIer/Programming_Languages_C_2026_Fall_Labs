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

    // if I get a file name from the command line I use that one instead
    if (argc > 1) {
        filename = argv[1];
    }

    // I open the file for writing, "w" makes a new file or empties the old one
    printf("Writing lines to %s...\n", filename);
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // I write two lines and close the file so everything gets saved
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fclose(fp);

    // now I open the same file again but this time to read it
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // I read it line by line until fgets returns NULL (end of file)
    printf("Reading contents:\n");
    while (fgets(line, sizeof line, fp) != NULL) {
        printf("%s", line);
        line_count++;
    }
    fclose(fp);

    printf("Lines read: %d\n", line_count);

    return EXIT_SUCCESS;
}
