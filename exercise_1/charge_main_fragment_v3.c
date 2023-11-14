
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
  int num_charges = 3;                               /* number of charges */
  int dim=3;                                  /* dimensionality of system */
  double q[num_charges];                              /* value of charges */
  double pos[num_charges][dim];                    /* position of charges */
  double x[dim];                                          /* space vector */
  double potential;                           /* for summing up potential */
  double r[num_charges];           /* absolute value of difference vector, squared */

  /** setup charges **/
  q[0] = 1; pos[0][0] = -1.025; pos[0][1] = 0; 
  pos[0][2] = 1.025;
  q[1] = -1; pos[1][0] = 1.025; pos[1][1] = 0; 
  pos[1][2] = -1.025;
  q[2] = 2; pos[2][0] = 1.025; pos[2][1] = 1.025; 
  pos[2][2] = 0;

  /** iterate over some positions **/
  for (x[0] = -2.0; x[0] <= 2.0; x[0] += 0.05){ /* iterate over x coordinate */
    for (x[1] = -2.0; x[1] <= 2.0; x[1] += 0.05){ /* iterate over y coordinate */
      for (x[2] = -2.0; x[2] <= 2.0; x[2] += 0.05){ /* iterate over z coordinate */
        potential = 0;
        for (int i = 0; i < num_charges; i++){
          double dx = pos[i][0] - x[0];
          double dy = pos[i][1] - x[1];

          // Check if the point coincides with a charge position
          if (dx == 0 && dy == 0) {
              potential = 0; // Set a default value to avoid division by zero
              break;         // Exit the loop since the potential is already determined
          }

          r[i] = 1.0 / sqrt(dx * dx + dy * dy);
          potential += q[i] * r[i];
        }
        printf("%f %f %f %f\n", x[0], x[1], x[2], potential);
      }
    }  
  }
  return(0);
}