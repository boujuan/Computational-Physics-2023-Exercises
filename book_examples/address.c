/*******************************************************************/
/*** Prints address of a variable                                ***/
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
  int sum;
  int *address1;

  address1 = &sum;
  printf("address = %p\n", address1);
  return(0);
}
