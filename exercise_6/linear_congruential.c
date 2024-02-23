/****************************************************************/
/*** Linear congruential generator                            ***/
/*** Rechnergest�tztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 100               /* number of bins in histogram */

int main(int argc, char *argv[]) 
{
  int a, c, m, I;              /* parameter of random-number generator */
  double number;                                   /* generated number */
  double number_old;                          /* store previous number */
  int num_runs;                  /* number of generated random numbers */     
  int histo[NUM_BINS];            /* histogram to measure distribution */
  double start_histo, end_histo;                 /* range of histogram */
  double delta;                                        /* width of bin */
  int bin;                                       /* bin for histogram */
  int t;                                               /* loop counter */
  
  m = 32768; c = 1; I = 1000;
  number_old = I/m;
  sscanf(argv[1], "%d", &num_runs);                 /* read parameters */
  sscanf(argv[2], "%d", &a);

  for(t=0; t<NUM_BINS; t++)                    /* initialise histogram */
      histo[t] = 0;        
  start_histo = 0.0; end_histo = 1;
  delta = (end_histo - start_histo)/NUM_BINS; 
  
  number_old = (double) I/m;
  for(t=0; t<num_runs; t++)                               /* main loop */
  {
    // Linear Congruential Generator formula. a is the multiplier, c is the increment, m is the modulus, and I is the seed.
    // I is the seed, and it is the previous number generated.
    // m is the modulus, and it is the maximum number that can be generated.
    // a is the multiplier, and it is the number that multiplies the previous number generated.
    // c is the increment, and it is the number that is added to the previous number generated.
    I = (a*I+c)%m;                    /* linear congruential generator */
    number = (double) I/m;                    /* map to interval [0,1) */
    bin = (int) floor((number-start_histo)/delta);
    // printf("%f %f\n", number_old, number);   /* uncomment: correl. */
    if( (bin >= 0)&&(bin < NUM_BINS))                /* inside range ? */
       histo[bin]++;                                    /* count event */
    number_old = number;
  }
  /*return(0);*/                         /* uncomment for correlation */
  // printf("# histogram of %d random numbers\n", num_runs);

  for(t=0; t<NUM_BINS; t++)              /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	histo[t]/(delta*num_runs));

  return(0);
}
