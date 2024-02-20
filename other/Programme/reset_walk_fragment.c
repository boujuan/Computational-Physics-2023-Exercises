/****************************************************************/
/*** Random walks with resetting                              ***/
/*** A.K. Hartmann January 2023                               ***/
/*** Computational Physics Course                             ***/
/*** University of Oldenburg, Germany 2023                    ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************* reset_step() *****************/
/** Performs one step: with probability p_reset  **/
/** the particle is set to zero. Else, it moves  **/
/** one site up or down, each with prob. 0.5     **/
/** PARAMETERS: (*)= return-paramter             **/
/**     x_old: current position                  **/
/**   p_reset: probability of reset              **/
/** RETURNS:                                     **/
/**     new position                             **/
/**************************************************/
double reset_step(double x_old, double p_reset)
{
	double p;
	double x;
	p = drand48();
	if (p <= p_reset)
	{
		x = 0;
	}
	else
	{
		p = drand48();
		if (p <= 0.5)
			x = x_old + 1; 
		else
			x = x_old - 1;
	}
	return(x);
}

int main(int argc, char **argv)
{
  double x, x0;                            /* current, target position (>0) */
  double t, t_max;                       /* step/time counter, maximum time */
  double p_reset, p_reset_max, steps;        /* reset probability of particle */
  double fpt_sum, fpt_sum2;       /* sum of first passage times, .. squared */
  int run, num_runs;                             /* many runs for averaging */
  int argz = 1;                                    /* counter for arguments */

  if(argc < 2)                        /* too few arguments -> error message */
  {
    fprintf(stderr, "USAGE: %s <x0> <p_reset>\n", argv[0]);
    exit(1);
  }

  sscanf(argv[argz++], "%lf", &x0);                     /* obtain arguments */
  sscanf(argv[argz++], "%lf", &p_reset_max);

  num_runs = 10000;
  t_max = 1e7;
  
  steps = 30;
  for(p_reset=0.001; p_reset<=p_reset_max; p_reset *= exp((log(p_reset_max)-log(0.001))/steps))
  {
      fpt_sum = 0; fpt_sum2 = 0;                          /* reset statistics */

      for(run=0; run<num_runs; run++)                 /* perform several runs */
      {
        x = 0;                                  /* particle starts at orginin */
        t = 0;
        while( (x<x0)&&(t<t_max) ) /* walk until target reached or too long */
        {
  		  x = reset_step(x, p_reset);
  		  t++;
        }
        if(t==t_max)                                 /* simulation too long ? */
        {
  		  fprintf(stderr, "# walk too long: abort\n");
  		  exit(1);
        }
        fpt_sum += t;                                    /* add to statistics */
        fpt_sum2 += t*t;
      }

      /* print mean first passage time and error bar */
      printf("%f %f %f\n", p_reset, fpt_sum/num_runs,
  	   sqrt( (fpt_sum2/num_runs - pow(fpt_sum/num_runs, 2))/num_runs) );
  }
  return(0);
}
