// week5_task2_struct_save_load.c
// Name: Şükrü Bedirhan  Surname: Hocuk  Student ID: 251ADB011
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

// my student record has a name, an age and a GPA
typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

int save_student(const Student *s, const char *filename);
int load_student(const char *filename, Student *out);

int main(void) {
    // I make the student that I want to save
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *filename = "student.txt";

    // I save the student, if it fails I stop the program
    printf("Saving student to file...\n");
    if (save_student(&s1, filename) != 0) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // I load it back into a different variable to see if saving worked
    printf("Loading student from file...\n");
    if (load_student(filename, &loaded) != 0) {
        fprintf(stderr, "Error: could not load student from %s\n", filename);
        return EXIT_FAILURE;
    }

    // I print it so I can compare it with the original
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}

// I write the student as one line like "Alice 21 3.75", I return 0 if it worked and -1 if not
int save_student(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);

    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

// I read the line back into out, I return 0 if it worked and -1 if not
int load_student(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    // I use %49s so a long name can not go past the 50 chars of the array
    int result = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);
    fclose(fp);

    // I need all 3 values, if I got less the file is broken
    if (result != 3) {
        return -1;
    }
    return 0;
}
