/*
 * week4_1_dynamic_array.c
 * Author: Şükrü Bedirhan Hocuk
 * Student ID: 251ADB011
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;
    long long sum = 0;
    double avg;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    avg = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", avg);

    free(arr);
    return 0;
}
