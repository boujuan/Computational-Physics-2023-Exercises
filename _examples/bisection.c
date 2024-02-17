/*******************************************************************/
/*** Provides a function search() which searches in int array    ***/
/*** via bisection for an entry.                                 ***/
/*** Sets up an array with integers numbers in increasing order  ***/
/*** Searches for a couple of sample numbers                     ***/
/*** (solution to exercise)                                      ***/
/***                                                             ***/
/*** Compile: cc -o bisection bisection.c -Wall                  ***/
/*** Run: bisection                                              ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Exercises                                          ***/
/*******************************************************************/

#include <stdio.h>

/*********************** search() *********************/
/** Searches an int array sorted in increasing order **/
/** for the occurence of a certain 'value'           **/
/** PARAMETERS: (*)= return-parameter                **/
/**        size: number of entries                   **/
/**      number: array                               **/
/**       value: to be found                         **/
/** RETURNS:                                         **/
/**     index of entry, -1 if not found              **/
/******************************************************/
int search(int size, int *number, int value)
{
  int top, bottom;     /* range where search is performed */
  int middle;                                /* mid point */

  top=size; bottom=0;   /* set initial range */
  while(bottom < top)  /* still something to search */
  {
    middle = (top+bottom)/2;
    if(number[middle] == value)
      return(middle);
    else if(number[middle] > value)
      top = middle-1;
    else
      bottom = middle+1;
  }
  if(number[bottom] == value)
    return(bottom);
  else if(number[top] == value)
    return(top);
  else
    return(-1);
}


int main()
{
  int size=100;   /* number of entries */
  int t;               /* loop counter */
  int number[size];   /* numbers */


  for(t=0; t<size; t++)  /* set up array */
    number[t] = 4*t;

  printf("%d found at %d\n", 120, search(size, number, 120));
  printf("%d found at %d\n", 0, search(size, number, 0));
  printf("%d found at %d\n", 396, search(size, number, 396));
  printf("%d found at %d\n", 35, search(size, number, 35));
  printf("%d found at %d\n", 2000, search(size, number, 2000));

  return(0);
}
  
