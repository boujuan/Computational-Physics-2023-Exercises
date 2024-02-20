/*******************************************************************/
/*** Exercises for pointer and pointers to pointers              ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Basic C programs                                   ***/
/*******************************************************************/

#include <stdio.h>

int main()
{
  double value;                                        /* a double */
  double *p1;                               /* address of a double */
  double **p2;                /* address of an address of a double */

  value = 33.3;                                   /* assign values */
  p1 = &value;
  p2 = &p1;

  printf("value = %f, &(value)=%p, &(&(value)) = %p,\n"
	 " value (via p1) = %f, value (via p2) = %f\n",
	 value, p1, p2, *p1, *(*(p2)) );

  return(0);
}
