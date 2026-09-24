#include <stdio.h>

/*
    Task:
    Write a function `long long factorial(int n)` that computes n!
    using a loop (not recursion).

    In main():
      - Ask user for an integer n
      - If n is negative, print an error and exit
      - Otherwise, call factorial and print the result
*/

long long factorial(int n) {
  long long result = 1;  // 0! = 1! = 1
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

int main(void) {
  int n;

  printf("Enter a non-negative integer n: ");
  if (scanf("%d", &n) != 1) {
    printf("Input error.\n");
    return 1;
  }

  if (n < 0) {
    printf("Error: n must be non-negative (n >= 0).\n");
    return 1;
  }

  printf("%d! = %lld\n", n, factorial(n));

  return 0;
}