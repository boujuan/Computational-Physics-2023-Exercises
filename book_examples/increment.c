/*******************************************************************/
/*** Illustrates use of increment and decrement operators        ***/
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
  int counter1, counter2, counter3, counter4;

  counter1 = 3;
  counter2 = counter1++;
  counter3 = ++counter1;
  counter4 = --counter1;
  printf("%d %d %d %d\n", counter1, counter2, counter3, counter4);
}
