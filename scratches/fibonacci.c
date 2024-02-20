/** 
 * Calculates Fibonacci number of 'n' dynamically.
 **/
#include <stdio.h>
#include <stdlib.h>

#include <math.h> // For INFINITY

double fib_dynamic(int n)
{
    double *fib, result;
    int t;

    if (n <= 2)
    {
        // Simple case
        return 1;
    }

    fib = (double *)malloc(n * sizeof(double));
    fib[1] = 1.0;
    fib[2] = 1.0;

    for (t = 3; t < n; t++)
    {
        fib[t] = fib[t - 1] + fib[t - 2];
    }

    result = fib[n - 1] + fib[n - 2];
    free(fib);

    return result;
}

// To calculate the maximum n that produces a finite result, we can use the following code:
int calculate_largest_n() {
    int n = 2; // Start from 2 as the first two Fibonacci numbers are 1
    double result = 0;

    while (1) {
        result = fib_dynamic(n);
        if (result == INFINITY) {
            return n - 1;
        }
        n++;
    }
}

int main() {
    int n = 10;
    double result = fib_dynamic(n);
    printf("The %dth Fibonacci number is: %f\n", n, result);

    // Test the maximum n that produces a finite result
    int max_n = calculate_largest_n();
    printf("The largest n that produces a finite result is: %d\n", max_n);
    return 0;
}