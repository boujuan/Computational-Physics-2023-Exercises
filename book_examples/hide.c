/*******************************************************************/
/*** Advanced example for using functions:                       ***/
/*** Hiding global variables                                     ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Functions                                          ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int number1, number2;    /* these are global variables */

/************** do_something() *******************/
/** Does nothing useful                         **/
/**                                             **/
/** Parameters: (*) = return parameter          **/
/**         ---                                 **/
/**                                             **/
/** Returns:                                    **/
/**       (nothing)                             **/
/*************************************************/
void do_something()
{
  int number1;    /* overides global definition */

  number1 = 33;
  printf("subr: n1=%d, n2=%d\n", number1, number2);
  number2 = 44;
  printf("subr: n1=%d, n2=%d\n", number1, number2);
}


int main()
{
  number1 = 11;
  number2 = 22;
  printf("main: n1=%d, n2=%d\n", number1, number2);
  do_something();
  printf("main: n1=%d, n2=%d\n", number1, number2);

  return(0);
}
