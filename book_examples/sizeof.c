/*******************************************************************/
/*** Prints number of bytes used for various data types          ***/
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
  printf("int uses %d bytes\n", sizeof(int));
  printf("short int uses %d bytes\n", sizeof(short int));
  printf("char uses %d bytes\n", sizeof(char));
  printf("long int uses %d bytes\n", sizeof(long int));
  printf("double uses %d bytes\n", sizeof(double));
  printf("float uses %d bytes\n", sizeof(float));
  printf("long double uses %d bytes\n", sizeof(long double));
  printf("pointers use %d bytes\n", sizeof(void *));
  return(0);
}
