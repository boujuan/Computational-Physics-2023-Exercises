/*******************************************************************/
/*** Calls some mathematical functions                           ***/
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
#include <math.h>

int main()
{
  double z= 0.25*M_PI; /* Set a variable z to 0.25 times pi */
  printf("%f %f %f\n", sin(z), cos(z), tan(z)); /* Print the sine, cosine, and tangent of z */
  printf("%f %f \n", asin(sqrt(2.0)/2.0)/M_PI, acos(0.0)/M_PI); /* Print the arcsine and arccosine of 0.5 */
  printf("%f %f %f %f\n", pow(M_E, 1.5), exp(1.5), log(1.0), log(M_E)); /* Print e^1.5, e^1.5, ln(1), and ln(e) */
  printf("%f %f %f\n", fabs(-3.4), floor(-3.4), floor(3.4)); /* Print the absolute value of -3.4, the floor of -3.4, and the floor of 3.4 */
  printf("%f %f\n", fmax(1.3, 2.67), fmin(1.3, 2.67)); /* Print the maximum of 1.3 and 2.67 and the minimum of 1.3 and 2.67 */
  printf("%e %e %e %e\n", erf(0.0), erf(1.0), erf(2.0), erf(5.0)); /* Print the error function of 0, 1, 2, and 5 */
  printf("%f %f %f %f\n", tgamma(4.0), tgamma(4.5), 
	                  tgamma(5.0), exp(gamma(5.0)) ); /* Print the gamma function of 4, 4.5, 5, and e to the gamma function of 5 */
  printf("%f %f %f\n", j0(2.0), j1(2.0), jn(1.0,2.0)); /* Print the Bessel function of the first kind of order 0, 1, and 2 */
  return(0); /* Return 0 */
}
