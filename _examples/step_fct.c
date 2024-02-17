/*******************************************************************/
/*** First example for using functions: step function            ***/
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


/************* step_function() *******************/
/** Mathematical step function:                 **/
/** Returns 0 if argument is less or equal to 0 **/
/**         and 1 else                          **/
/**                                             **/
/** Parameters: (*) = return parameter          **/
/**         x: mathematical argument            **/
/*                                              **/
/** Returns:                                    **/
/**       function value                        **/
/*************************************************/
  double step_function(double x)
  {
    if(x <= 0.0)
      return(0.0);
    else
      return(1.0);
  }




int main()
{
  double x;
  for(x=-1.0; x<=1.0; x+=0.1)     /* print step function in [-1,1] */
    printf("Theta(%f)=%f\n", x, step_function(x));

  return(0);
}

