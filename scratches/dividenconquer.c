// Sorting of a set of elements {a0 , . . . , an−1 } by Mergesort.
// Basic idea: divide set into two sets of equal size, sort both sets and merge
// them such that the result is sorted.

#include <stdio.h>

/** sorts ’n’ integer numbers in the array ’a’ in ascending **/
/** order using the mergsort algorithm **/
void my_mergesort(int n, int *a) {
    int *b, *c; // two arrays
    int n1, n2; // sizes of the two arrays
    int t, t1, t2; // (loop) counters

    if(n <= 1) {
        return; // at most one element ? nothing to do
    }

    n1 = n / 2; 
    n2 = n - n1; // calculate half sizes

    // array a is distributed to b,c. Note: one could do it
    // using one array alone, but yields less clear algorithm
    b = (int *) malloc(n1 * sizeof(int));
    c = (int *) malloc(n2 * sizeof(int));

    for(t = 0; t < n1; t++) { // copy data
        b[t] = a[t];
    }

    for(t = 0; t < n2; t++) {
        c[t] = a[t + n1];
    }

    my_mergesort(n1, b); // recursive call to sort first array
    my_mergesort(n2, c); // sort two smaller arrays

    t1 = 0; 
    t2 = 0; // assemble solution from subsolutions

    for(t = 0; t < n; t++) {
        if(((t1 < n1) && (t2 < n2) && (b[t1] < c[t2])) || (t2 == n2)) {
            a[t] = b[t1++];
        } else {
            a[t] = c[t2++];
        }
    }

    free(b); 
    free(c);
}

void printArray(int A[], int size) {
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// Example to test the merge sort
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    my_mergesort(arr_size, arr);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}