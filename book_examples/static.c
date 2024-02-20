/*******************************************************************/
/*** Advanced example for using functions:                       ***/
/*** Use of static variables                                     ***/
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


/************** do_something() *******************/
/** Prints number passed and returns how often  **/
/** it was called                               **/
/**                                             **/
/** Parameters: (*) = return parameter          **/
/**         n: some number                      **/
/**                                             **/
/** Returns:                                    **/
/**       number of times function was called   **/
/*************************************************/
int do_something(int n)
{
  static int num_calls = 0;

  printf("I got:%d\n", n);

  return(++num_calls);
}


int main(int argc, char**argv)
{
  int i;

  for(i=0; i<100; i++)
    printf("The function was called %d times\n", do_something(4*i));

  return(0);
}
