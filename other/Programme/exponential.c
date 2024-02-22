/****************************************************************/
/*** Generator for exponentially distributed numbers          ***/
/*** Rechnergest�tztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 100

/*********************  rand_U() *****************/
/** Generates random number, which is          **/
/** uniformly distrbuted in [0,\lambda)        **/
/** PARAMETERS: (*)= return-paramter           **/
/**     lambda: parameter of distribution      **/
/** RETURNS:                                   **/
/**      random number                         **/
/************************************************/
double rand_U(double lambda)
{
  double value;
  do
    value = ((double)rand())/(RAND_MAX);
  while(value == 1.0);
  return(value*lambda);
}


int main(int argc, char *argv[])
{
  int histo[NUM_BINS];                                    /* histogram */
  int bin;
  double start_histo, end_histo;                 /* range of histogram */
  double delta;                                        /* width of bin */
  int t;                                               /* loop counter */
  int num_runs;                  /* number of generated random numbers */     
  double lambda;                          /* parameter of distribution */
  double number;                                   /* generated number */

  num_runs = atoi(argv[1]);                         /* read parameters */
  sscanf(argv[2], "%lf", &lambda);

  for(t=0; t<NUM_BINS; t++)                    /* initialise histogram */
      histo[t] = 0;        
  start_histo = 0.0; end_histo = 10.0/lambda;
  delta = (end_histo - start_histo)/NUM_BINS; 
  
  for(t=0; t<num_runs; t++)                               /* main loop */
  {
    number = -log(rand_U(1.0))/lambda;   /* generate exp-distr. number */
    bin = (int) floor((number-start_histo)/delta);
    if( (bin >= 0)&&(bin < NUM_BINS))                /* inside range ? */
       histo[bin]++;                                    /* count event */
  }

  for(t=0; t<NUM_BINS; t++)              /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	     histo[t]/(delta*num_runs));

  return(0);
}