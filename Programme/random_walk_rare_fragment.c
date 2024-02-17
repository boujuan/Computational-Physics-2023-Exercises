/*************************************************************/
/*** Simulate random walk distribution                     ***/
/*** For N values d_1,...,d_n of a distribution            ***/
/*** sum = sum{d_1,...,d_n} is taken and a histogram of    ***/
/*** the sum is recorded.                                  ***/ 
/*** The walks ar subject to a Markov chain with a bias    ***/
/*** exp(-sum/T) with "temperature" T, so the tails of the ***/
/*** distribution are accessible                           ***/
/*** Practial work for lecture                             ***/
/*** Advanced computer simulations                         ***/
/*** WS 2022/23 University of Oldenburg                    ***/
/*** A.K. Hartmann                                         ***/
/*************************************************************/
  
/*** Vers. History                                                      ***/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 100


/* one configuration */
typedef struct
{
  int         num;
  double   *delta;
  double       sum;
} config_t;


/********************* rw_step() ****************/
/** Generates random number -1/1, which has    **/
/** probability p(1)=lambda, p(-1)=1-lambda    **/
/** PARAMETERS: (*)= return-paramter           **/
/**    lambda: parameter of distribution       **/
/** RETURNS:                                   **/
/**      random number                         **/
/************************************************/
double rw_step(double lambda)
{
  if(drand48() < lambda)
    return(1);
  else
    return(-1);
}


/******************** rw_sum() ******************/
/** Returns sum of num numbers                 **/
/** PARAMETERS: (*)= return-paramter           **/
/**     delta: step values                     **/
/**       num: number of values                **/
/** RETURNS:                                   **/
/**      sum                                   **/
/************************************************/
double rw_sum(double *delta, int num)
{
  double sum;
  int t;

  sum = 0;
  for(t=0; t<num; t++)
    sum += delta[t];

  return(sum);
}


/******************* rw_mc_step() *****************/
/** Peforms several Metropolis MC steps with the **/
/** sum  of 'cfg.delta' as "energy" E. The       **/
/** target distribution is the Boltzmann         **/
/** distribution ~exp(-E/T). In each step        **/
/** one value is changed in 'cfg.delta'          **/
/** PARAMETERS: (*)= return-paramter             **/
/**       cfg: configuration, includes delta and **/
/**            num = number of values            **/
/**         T: temperature (>0 or <0)            **/
/** num_mc_steps: how many values are redrawn ?  **/
/**    lambda: parameter of distribution         **/
/** RETURNS:                                     **/
/**      number of accepted moves                **/
/**************************************************/
int rw_mc_step(config_t *cfg, double T, int num_mc_steps,
		    double lambda)
{
  int mc_step;                                         /* main loop counter */
  double old_delta;                                 /* store previous value */
  int pos;                                       /* where value was changed */
  double sum_old;                                      /* previous "energy" */
  double prob;                                    /* Metropolis probability */
  int num_accepted = 0;

  for(mc_step=0; mc_step<num_mc_steps; mc_step++)     /* loop over mC steps */
  {
    sum_old = cfg->sum;
	
	pos = floor(drand48()*cfg->num);
	old_delta = cfg->delta[pos];
	cfg->delta[pos] = rw_step(lambda); 
	cfg->sum = rw_sum(cfg->delta, cfg->num);
	prob = exp(-(cfg->sum-sum_old)/T);
	if(prob>=1)
		prob = 1;
	if(drand48()<=prob)
		num_accepted++;
	else
	{
		cfg->delta[pos] = old_delta;
		cfg->sum = sum_old;
	}
  }
  return(num_accepted);
}


int main(int argc, char **argv)
{
  int t;                                        /* counters for interations */
  int step, num_steps;                 /* how often MC sweeps are performed */
  int start_measure;                                  /* equilibration time */
  double *histo;                                               /* histogram */
  double num_bins, num_entries;
  double accepted;  /* count number of accepted moves */
  int bin;
  config_t cfg;
  double start_histo, end_histo;                      /* range of histogram */
  double delta;                                             /* width of bin */

  double lambda;                               /* parameter of distribution */
  double T;   /* temperature of biased simulation */
  double sum;                   /* sum = final pos of random walk */
  int argz = 1;   /* counter for treating argument */

  int do_show_series = 1;           /* show all values instead of histogram */
  FILE *histofile;
  char filename[200];

  if(argc != 5)
  {
    printf("USAGE: %s  <N> <lambda> <MC steps> <T>\n", argv[0]);
    exit(1);
  }

  cfg.num = atoi(argv[argz++]);                          /* read parameters */
  sscanf(argv[argz++], "%lf", &lambda);
  num_steps = atoi(argv[argz++]);                   
  sscanf(argv[argz++], "%lf", &T);


  cfg.delta = (double *) malloc(cfg.num*sizeof(double));
  
  start_measure = num_steps/10;
  num_bins = cfg.num+1;
  histo = (double *) malloc(num_bins*sizeof(double));

  for(t=0; t<num_bins; t++)                          /* initialise histogram */
      histo[t] = 0;        
  start_histo = -cfg.num-1; 
  end_histo = cfg.num+1;                                 /* for random walks */
  delta = (end_histo - start_histo)/num_bins; 
  
  for(t=0; t<cfg.num; t++)
  {
    cfg.delta[t] = rw_step(lambda);                    /* generate all steps */
  }
  cfg.sum = rw_sum(cfg.delta, cfg.num);

  num_entries = 0;
  accepted = 0;
  for(step=0; step<num_steps; step++)                           /* main loop */
  {
    accepted += 
      rw_mc_step(&cfg, T, cfg.num, lambda);  /* make cfg.num steps:one sweep */
     
    sum = rw_sum(cfg.delta, cfg.num);

    if(do_show_series)
      printf("%d %f\n", step, sum);

    if(step > start_measure )
    {
      bin = (int) floor((cfg.sum-start_histo)/delta);
      if( (bin >= 0)&&(bin < num_bins))                   /* inside range ? */
      {
	histo[bin]++;                                        /* count event */
	num_entries++;
      }
    }
  }

  printf("# rate of accepted moves: %f\n", accepted/(cfg.num*num_steps));

  sprintf(filename, "rw_N%d_l%3.2f_mcT%4.3f.histo", cfg.num, lambda, T);
  histofile = fopen(filename, "w");
  fprintf(histofile, "# %d measurement points for N=%d, T=%4.3f\n",
	  (int) num_entries, cfg.num, T);
  for(t=0; t<num_bins; t++)                   /* print normalized histogram */
    fprintf(histofile, "%f %e\n", start_histo + (t+0.5)*delta,
	    histo[t]/(delta*num_entries));
  fclose(histofile);
  
  free(cfg.delta);
  free(histo);

  return(0);
}
