#include <stdio.h>

  struct particle 
  {
    double        mass;         /* in kg                        */ 
    int         charge;         /* in units of e                */
    double  position[3];         /* position in space. in meters */
  };

typedef double vector_t[3];
typedef struct particle particle_t;

particle_t initialise_atom()
{
  particle_t atom;
  atom.mass = 1.0;

  return(atom);
}

int main()
{
  vector_t v1;

  particle_t part1;
  
  
  part1.mass = 9.1e-31;
  part1.charge = 1;
  part1.position[0] = -2.3e-3;
  printf("%e\n", part1.mass);

  v1[0] = 3.2;
  printf("%f\n", v1[0]);
  return(0);
}

