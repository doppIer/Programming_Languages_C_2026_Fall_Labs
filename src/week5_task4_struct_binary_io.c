// week5_task4_struct_binary_io.c   (BONUS)
// Name: Şükrü Bedirhan  Surname: Hocuk  Student ID: 251ADB011
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

// Same student record as in Task 2
typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

int  save_student_binary(const Student *s, const char *filename);
int  load_student_binary(const char *filename, Student *out);
long file_size(const char *filename);

int main(void) {
    // {0} fills the struct with zeros so no random bytes go into the file
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    // Save the struct as raw bytes
    printf("Saving student in binary format...\n");
    if (save_student_binary(&s1, bin_file) != 0) {
        perror(bin_file);
        return EXIT_FAILURE;
    }

    // Save the same record as text so we can compare file sizes
    FILE *fp = fopen(txt_file, "w");
    if (fp == NULL) {
        perror(txt_file);
        return EXIT_FAILURE;
    }
    fprintf(fp, "%s %d %.2f\n", s1.name, s1.age, s1.gpa);
    fclose(fp);

    // Read the raw bytes back into a struct
    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_file, &loaded) != 0) {
        fprintf(stderr, "Error: could not load student from %s\n", bin_file);
        return EXIT_FAILURE;
    }

    // The binary file is bigger: it stores the whole 50-byte name array plus padding
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    printf("Text file size: %ld bytes\n", file_size(txt_file));
    printf("Binary file size: %ld bytes\n", file_size(bin_file));

    return EXIT_SUCCESS;
}

// Writes the whole struct to the file in binary. Returns 0 on success, -1 on error.
int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }

    // fwrite returns how many structs were written; we expect exactly 1
    size_t written = fwrite(s, sizeof(Student), 1, fp);
    if (fclose(fp) != 0 || written != 1) {
        return -1;
    }
    return 0;
}

// Reads one struct from the binary file into out. Returns 0 on success, -1 on error.
int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // fread returns how many structs were read; we expect exactly 1
    size_t read = fread(out, sizeof(Student), 1, fp);
    fclose(fp);

    if (read != 1) {
        return -1;
    }
    return 0;
}

// Returns the size of the file in bytes, or -1 on error.
long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // Jump to the end of the file; the position there equals the size
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);
    fclose(fp);
    return size;
}
