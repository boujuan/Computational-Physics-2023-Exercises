/****************************************************************/
/*** Draw random number using the rejection method            ***/
/*** Rechnergestütztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 100

/** gerenates random number for 'pdf' in the range **/
/** ['x0', 'x1'). condition: pdf(x)<='p_max' in    **/
//* the range ['x0', 'x1')                         **/
double reject(double p_max, double x0, double x1, 
	      double (* pdf)(double))
{
  int found;                 /* flag if valid number has been found */
  double x,y;                 /* random points in [x0,x1]x[0,p_max] */
  found = 0;
  while(!found)                   /* loop until number is generated */
  {
    x = x0 + (x1-x0)*drand48();             /* uniformly on [x0,x1] */
    y = p_max *drand48();                 /* uniformly in [0,p_max] */
    if(y <= pdf(x))                                     /* accept ? */
	found = 1;
  }
  return(x);
}

/** artifical pdf **/
double pdf(double x)
{
  if( (x<0)||
      ((x>=0.5)&&(x<1))||
      (x>1.5) )
      return(0);
  else if((x>=0)&&(x<0.5))
      return(1);
  else
      return(4*(x-1));
}



int main(int argc, char *argv[])
{
  int histo[NUM_BINS];                                 /* histogram */
  int bin;
  double start_histo, end_histo;              /* range of histogram */
  double delta;                                     /* width of bin */
  int t;                                            /* loop counter */
  int num_runs;               /* number of generated random numbers */     
  double number;                                /* generated number */

  num_runs = atoi(argv[1]);                      /* read parameters */

  for(t=0; t<NUM_BINS; t++)                 /* initialise histogram */
      histo[t] = 0;        
  start_histo = 0.0; end_histo = 2;
  delta = (end_histo - start_histo)/NUM_BINS; 
  
  for(t=0; t<num_runs; t++)                            /* main loop */
  {
    number = reject(2, 0, 1.5, pdf);             /* generate number */
    bin = (int) floor((number-start_histo)/delta);
    if( (bin >= 0)&&(bin < NUM_BINS))             /* inside range ? */
       histo[bin]++;                                 /* count event */
  }

  for(t=0; t<NUM_BINS; t++)           /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	     histo[t]/(delta*num_runs));

  return(0);
}
