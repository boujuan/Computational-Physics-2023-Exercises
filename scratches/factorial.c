#include <stdio.h>
#include <stdlib.h>

double factorial(int n) {
    if(n==1)
        return(1.0);
    else
        return(n*factorial(n-1));
}

double factorial_iterative(int n) {
    double result = 1.0;
    for(int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        exit(1);
    }
    int num = atoi(argv[1]);
    double result = factorial(num);
    printf("The factorial of %d is %.2f\n", num, result);

    // Test the iterative version
    double result_iterative = factorial_iterative(num);
    printf("The factorial of %d is %.2f\n", num, result_iterative);

    return 0;
}