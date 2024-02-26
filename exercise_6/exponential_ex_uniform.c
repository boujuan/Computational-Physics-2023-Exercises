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
#include <math.h>

double rand_U(double lambda) // Generates random number uniformly distributed in range [0,lambda)
{
  double value;
  do
    value = ((double)rand())/(RAND_MAX);
  while(value == 1.0);
  return(value*lambda);
}

double gumbell(double lambda, double x, double z0) // Gumbell distribution
{
  double z = (x - z0)/lambda;
  return exp(-z - exp(-z))/lambda;
}

// double uniform_density(double N, double z, double a, double b) {
//     if (z < a || z > b) {
//         return 0;
//     }

//     double p = 1.0 / (b - a); //pdf
//     double P = (z - a) / (b - a);

//     return N * p * pow(P, N - 1);
// }

int main(int argc, char *argv[]) // Input args: num_runs, lambda, N (numb of random numbers to generate)
{
  int histo[NUM_BINS];                                    /* histogram */
  int bin;
  double start_histo, end_histo;                 /* range of histogram */
  double delta;                                        /* width of bin */
  int t;                                               /* loop counter */
  int num_runs;                  /* number of generated random numbers */     
  double lambda;                          /* parameter of distribution */
  double number;                                   /* generated number */

  int t2; // Added loop counter
  int N;  // Number of random numbers to generate
  double max_N; // Max number each iteration

  num_runs = atoi(argv[1]);                         /* read parameters */
  sscanf(argv[2], "%lf", &lambda);          // Lambda input arg converted to string
  N = atoi(argv[3]);  // 3rd input arg


  for(t=0; t<NUM_BINS; t++)                    /* initialise histogram */
      histo[t] = 0;        
  start_histo = 0.0; end_histo = 10.0/lambda;
  delta = (end_histo - start_histo)/NUM_BINS; 
  
  for(t=0; t<num_runs; t++)                               /* main loop */
  {
    // max_N = -log(rand_U(1.0))/lambda;   // Exponential distribution for first number
    //TODO: Uniform distribution for first number
    //max_N = rand_U(lambda);
    max_N = rand_U(lambda);
    for(t2=0; t2<N; t2++) {
      number = rand_U(lambda)/lambda;   /* generate exp-distr. number */
      if(number > max_N) {
        max_N = number;
      }
    }
    bin = (int) floor((max_N-start_histo)/delta); // CHange this to take max_N
    if( (bin >= 0)&&(bin < NUM_BINS))                /* inside range ? */
       histo[bin]++;                                    /* count event */
  }

  // for(t=0; t<NUM_BINS; t++)              /* print normalized histogram */
  //     printf("%f %f\n", start_histo + (t+0.5)*delta,
	//      histo[t]/(delta*num_runs));

  // double z0 = log(N)/lambda; // Gumbell distribution parameter

  // for(double x = 0; x < 10.0/lambda; x += 0.1) {
  //   printf("%f %f\n", x, gumbell(lambda, x, z0));
  // }

  // Print both the histogram and the Gumbell distribution together
  for(t=0; t<NUM_BINS; t++) { /* print normalized histogram */
    double x = start_histo + (t+0.5)*delta;
    double y = histo[t]/(delta*num_runs);
    double z0 = log(N)/lambda;
    double z = gumbell(lambda, x, z0); // Gumbell distribution value
    printf("%f %f %f\n", x, y, z);
  }

  return(0);
}
