/****************************************************************/
/*** Simulation of totally assymetric exclusion process       ***/
/*** A.K. Hartmann December 2014                              ***/
/*** Computeroriented Physics                                ***/
/*** University of Oldenburg, Germany 2014                    ***/
/****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
  double alpha;   /* probability of inserting a particle */
  double beta;    /* probability of exiting a particle */
  int L;          /* number of sites */
  int *site;      /* array of sites */
} tasep_sys_t;




/******************* tasep_sweep() *******************/
/** Performs one sweep:                             **/
/** 1. possibly empties last site (prob. sys->beta) **/
/** 2. advances particles inside system (prob. 0.5) **/
/** 3. possibly occupies 1st site (prob. sys->alpha)**/
/** PARAMETERS: (*)= return-paramter                **/
/**      (*) sys: ptr to system                     **/
/** RETURNS:                                        **/
/**   current                                       **/
/*****************************************************/
double tasep_sweep(tasep_sys_t *sys)
{
  int num_hops;
  int t;      /* loop counter */

  num_hops = 0;
  /* if last site is occupied: empty with probability sys->beta: */
  if( (sys->site[sys->L-1] == 1) && (drand48() < sys->beta))
  {
    sys->site[sys->L-1] = 0;
    num_hops++;
  }

  /* advance particles with prob. 0.5 if successor is empty */
  /** COMPLETE HERE **/


  /* if first site is empty, occupy with prob. sys->alpha: */
  /** COMPLETE HERE **/


  return((double) num_hops/sys->L);
}

/** IMPLEMENT HERE A FUNCTION tasep_density() TO OBTAIN THE DENSITY **/


int main(int argc, char **argv)
{
  int seed;                               /* of random number generator */
  int sweep, num_sweeps;   /* current/total number of simulation sweeps */
  tasep_sys_t sys;                                     /* actual system */
  int argz = 1;              /* counter to treat command-line arguments */
  int t;                                                /* loop counter */
  double current = 0;                           /* current of particles */
  double density = 0;                               /* particle density */

  seed = 1000;
  srand48(seed);

  if(argc - argz < 4)
  {
    printf("USAG:E %s <L> <alpha> <beta> <#sweeps>\n", argv[0]);
    exit(1);
  }
  sys.L = atoi(argv[argz++]);
  sscanf(argv[argz++], "%lf", &sys.alpha);
  sscanf(argv[argz++], "%lf", &sys.beta);
  num_sweeps = atoi(argv[argz++]);

  sys.site = (int *) malloc(sys.L * sizeof(int));         /* initialize */
  for(t=0; t<sys.L; t++)
    sys.site[t] = 0;


  /** main simulation loop **/
  for(sweep=0; sweep<num_sweeps; sweep++)
  {
    current = tasep_sweep(&sys);
    /** COMPLETE HERE: density = ; **/

    /** COMPLETE RUNNING AVERAGES, ALSO PRINTING THEM **/
    printf("%d %f %f\n", sweep, current, density);
  }

  free(sys.site);                                       /* free memory */
  return(0);
}
