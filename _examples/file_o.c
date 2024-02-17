/*******************************************************************/
/*** Advanced examples for using printf():                       ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Input/Output                                       ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(int argc, char**argv)
{
  double x;
  FILE *file_p;

  file_p = fopen("funcs.dat", "w");     /* open file for writing */

  fprintf(file_p, "#    x    cos(x)   sin(x)   exp(x)\n");

  for(x=0; x<=2*M_PI; x+=0.1)              /* write fcts to file */
    fprintf(file_p, "%f %f %f %f\n", x, sin(x), cos(x), exp(x));
 
  fclose(file_p);                                  /* close file */

  return(0);
}
