/*******************************************************************/
/*** Program for calculating the potential for a two-dimensional ***/
/*** charge distribution                                         ***/
/***                                                             ***/
/*** Lecture: Computational Physics                              ***/
/*** A.K. Hartmann 2011                                          ***/
/***                                                             ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************** main program *********************************/
int main(int argc, char **argv)
{
  int num_charges = 2;                               /* number of charges */
  int dim=2;                                  /* dimensionality of system */
  double q[num_charges];                              /* value of charges */
  double pos[num_charges][dim];                    /* position of charges */
  int c;                                                      /* counters */
  double x[dim];                                          /* space vector */
  double potential;                           /* for summing up potential */
  double dr;                       /* difference (in a certain direction) */
  double r, r2;           /* absolute value of difference vector, squared */
  int d;                                             /* dimension counter */

  /** setup charges **/
  q[0] = 1; pos[0][0] = -1.025; pos[0][1] = 0; /* charge 0, position x=-1.025, y=0 */
  q[1] = -1; pos[1][0] = 1.025; pos[1][1] = 0; /* charge 1, position x=1.025, y=0 */

  x[0] = 1.0; x[1] = -0.5;  /* example for setting position */
  /** iterate over some positions **/
  /** COMPLETE THE MAIN PROGRAM HERE:                        **/
  /** ITERATE SUITABLY x[0],x[1] AND OUTPUT EACH TIME x[0] x[1] V(x)   **/

  for (x[0] = -2.0; x[0] <= 2.0; x[0] += 0.05){ /* iterate over x coordinate */
    for (x[1] = -2.0; x[1] <= 2.0; x[1] += 0.05){ /* iterate over y coordinate */

      r = sqrt(pow(pos[0][0] - x[0], 2) + pow(pos[0][1] - x[1], 2)); /* squared difference vector of distance to charge 0 in the xy plane */
      r2 = sqrt(pow(pos[1][0] - x[0], 2) + pow(pos[1][1] - x[1], 2)); /* squared difference vector of distance to charge 1 in the xy plane */
      potential = q[0]/r + q[1]/r2; /* sum of potential of charge 0 and charge 1 */

      // printf("%f\n%f", potential);  /* POSSIBLY OUTPUT x[0], x[1] HERE **/
      // printf("[ x0=%.3f, y0=%.3f ], [ V(x) = %.6f ]\n", x[0], x[1], potential);
      printf("%f %f %f\n", x[0], x[1], potential);

    }
  }
  return(0);
}