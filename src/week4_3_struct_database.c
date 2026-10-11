/*
 * week4_3_struct_database.c
 * Author: Şükrü Bedirhan Hocuk
 * Student ID: 251ADB011
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int n;
    struct Student *students = NULL;
    float total = 0.0f;
    int best = 0;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    students = malloc((size_t)n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);
        if (scanf("%49s %d %f", students[i].name, &students[i].id, &students[i].grade) != 3) {
            printf("Invalid input.\n");
            free(students);
            return 1;
        }
    }

    printf("\n");
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
    for (int i = 0; i < n; i++) {
        printf("%-6d %-11s %.1f\n", students[i].id, students[i].name, students[i].grade);
        total += students[i].grade;
        if (students[i].grade > students[best].grade) {
            best = i;
        }
    }

    printf("\nAverage grade = %.2f\n", total / n);
    printf("Top student: %s (%.1f)\n", students[best].name, students[best].grade);

    free(students);
    return 0;
}
