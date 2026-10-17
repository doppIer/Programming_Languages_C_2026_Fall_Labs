// week5_task3_student_management_system.c
// Name: Şükrü Bedirhan  Surname: Hocuk  Student ID: 251ADB011
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

// my student record has a name, an ID and a GPA
typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

int  load_students(Student arr[], int max);
int  save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    // I load the students that were saved last time (on the first run there are none)
    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;                         // end of input: save and exit instead of looping forever
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;   // non-numbers become invalid
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count);
                break;
            case 3:
                // I save everything to the file before I quit
                if (save_students(students, count) != 0) {
                    perror(DATA_FILE);
                    fprintf(stderr, "Error: could not save data to %s\n", DATA_FILE);
                    return EXIT_FAILURE;
                }
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

// I read the students from the file into arr and return how many I loaded
int load_students(Student arr[], int max) {
    // if the file is not there yet it is not an error, I just have 0 students
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return 0;
    }

    char line[LINE_LEN];
    int count = 0;

    // I stop at max so I never write outside the array
    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        Student s = {0};
        // I only keep the line if I could read name, ID and GPA, bad or empty lines are skipped
        if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
            arr[count] = s;
            count++;
        }
    }

    fclose(fp);
    return count;
}

// I write all students to the file (the old content is replaced), I return 0 if it worked and -1 if not
int save_students(const Student arr[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        return -1;
    }

    // I write one student per line like "Alice,101,3.80"
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }

    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

// I ask the user for a new student, check the input and add it to the array
void add_student(Student arr[], int *count) {
    char name[LINE_LEN];
    char id_buf[LINE_LEN];
    char gpa_buf[LINE_LEN];
    char *end;

    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    // I read all three answers as text first and check them after
    if (read_line("Enter name: ", name, sizeof name) != 0) {
        return;
    }
    if (read_line("Enter ID: ", id_buf, sizeof id_buf) != 0) {
        return;
    }
    if (read_line("Enter GPA: ", gpa_buf, sizeof gpa_buf) != 0) {
        return;
    }

    // the name can not be empty, can not have a comma (that would break my file) and has to fit
    if (name[0] == '\0' || strchr(name, ',') != NULL || strlen(name) >= NAME_LEN) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // the ID has to be a whole number with nothing after it
    long id = strtol(id_buf, &end, 10);
    if (end == id_buf || *end != '\0') {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // the GPA has to be a number between 0.0 and 4.0
    float gpa = strtof(gpa_buf, &end);
    if (end == gpa_buf || *end != '\0' || gpa < 0.0f || gpa > 4.0f) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // everything is ok so I put the student at the end of the array
    Student s = {0};
    strcpy(s.name, name);
    s.id = (int)id;
    s.gpa = gpa;

    arr[*count] = s;
    (*count)++;
    printf("Student added successfully!\n");
}

// I print all students as a small table
void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}
