/*******************************************************************/
/*** Integrates a function by simply approximating it by a sum   ***/
/*** (solution to exercise)                                      ***/
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
#include <math.h>

/******************** integrate() *********************/
/** Integrates a 1-dim function numerically using    **/
/** the trapezoidal rule                             **/
/** Improved version contributed by                  **/
/** Tom Seren, Espoo, Finland                        **/
/** PARAMETERS: (*)= return-parameter                **/
/**        from: startpoint of interval              **/
/**          to: endpoint of interval                **/
/**   num_steps: number of integration steps         **/
/**           f: p. to function to be integrated     **/
/** RETURNS:                                         **/
/**     value of integral                            **/
/******************************************************/
double integrate(double from, double to, int num_steps, 
		 double (* f)(double))
{
  int step;                                    /* loop counter */
  double delta;              /* width of one integrateion step */
  double sum;                              /* integrated value */
  double x;                                /* current argument */
  double save1, save2;
  
  delta = (to-from)/num_steps;
  sum = 0.0;
  x = from; save1 = f(x);
  for(step=0; step<num_steps; step++)   /* perform integration */
  {
      save2 = f(x+delta);
      sum += save1 + save2;
      x += delta; save1 = save2;
  }
  return(0.5*delta*sum);
}


int main()
{
  int num_steps = 1000;          /* number of integration steps */

  printf("Int(0,PI/2) sin(x) = %f\n", 
	 integrate(0, M_PI/2, num_steps, sin));
  printf("Int(0,PI) sin(x) = %f\n", 
	 integrate(0, M_PI, num_steps, sin));
  printf("Int(0,1.5*PI) sin(x) = %f\n", 
	 integrate(0, 1.5*M_PI, num_steps, sin));
  printf("Int(0,2*PI) sin(x) = %f\n", 
	 integrate(0, 2*M_PI, num_steps, sin));

  return(0);
}
