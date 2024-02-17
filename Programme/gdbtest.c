/*******************************************************************/
/*** Test program for demonstrating how to debug                 ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Debugging                                          ***/
/*** Section: gdb                                                ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>


int chksum(int n, int *array)
{
  int sum=0, t;
  for (t=0; t<n; t++)
    sum += array[t];
  return(sum);
}


int main(int argc, char *argv[])
{
    int t, *array, sum = 0;

    array = (int *) malloc (100*sizeof(int));
    for(t=0; t<100; t++)
        array[t] = t;
    for(t=0; t<100; t++)
        sum += array[t];
    printf("sum= %d\n", sum);
    free(array);
    return(0);
}
