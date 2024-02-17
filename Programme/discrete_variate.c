/****************************************************************************/
/*** Generator discrete random numbers                                    ***/
/*** A.K. Hartmann December 2011                                          ***/
/*** Computerorientierte Physik                                           ***/
/*** University of Oldenburg, Germany 2011                                ***/
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 20

typedef struct
{
  int num_entries;     /* number of events */
  double *q;       /* splitting probabilities */
  int *a;       /* events for rand<=q */
  int *b;       /* events for rand>q  */
} discrete_variate_t;


/******************* setup_table() *********************/
/** Sets up table to generate discrete random numbers **/
/** in constant time using the Walkers method, as     **/
/** implemented in K. Fuki and S. Todo, J. Comp. Phys.**/
/** 228 (2009) 2629-2642                              **/
/** PARAMETERS: (*)= return-paramter                  **/
/**     num_entries: number of possible results       **/
/**        p: original probabilities                  **/
/** RETURNS:                                          **/
/**      table with auxiliary variables               **/
/*******************************************************/
discrete_variate_t setup_table(int num_entries, double *p)
{
  int t, t0, t1, swap_a;
  discrete_variate_t table;
  double average_prob, swap_q;

  /* initialise table */
  table.num_entries = num_entries;
  table.q = (double *) malloc(num_entries*sizeof(double));
  table.a = (int *) malloc(num_entries*sizeof(int));
  table.b = (int *) malloc(num_entries*sizeof(int));
  for(t=0; t<num_entries; t++)
  {
    table.q[t] = p[t];
    table.a[t] = t;
    table.b[t] = -1;
  }

  average_prob = 1.0/num_entries;
  t0 = 0;
  t1 = num_entries-1;

  /** arrange elements such that all elements with **/
  /** q[t] > average_prob come first.              **/
  while (t0 <= t1)
  {
	  if ((table.q[t0]>average_prob) && (table.q[t1]<=average_prob))
	  {
		  t0++;
		  t1--;
	  }
	  else if ((table.q[t0]>average_prob) && (table.q[t1]>average_prob))
	  {
		  t0++;
	  }
	  else if ((table.q[t0]<=average_prob) && (table.q[t1]<=average_prob))
	  {
		  t1--;
	  }
	  else if ((table.q[t0]<=average_prob) && (table.q[t1]>average_prob))
	  {
		  swap_a = table.a[t0];
		  swap_q = table.q[t0];
		  table.a[t0] = table.a[t1];
		  table.q[t0] = table.q[t1];
		  table.a[t1] = swap_a;
		  table.q[t1] = swap_q;	
	  }
  }
	
  /* now t1 points to the rightmost element larger than average_prob */
  
  /* rearrange table such that "each entry represents 'average_prob'" */
  for(t=num_entries -1; t>=1; t--)
  {
  	table.b[t] = table.a[t1];
	table.q[t1] = table.q[t1] - (average_prob-table.q[t]);
	if (table.q[t1] <= average_prob)
		t1--;
  }
	  	  
  for(t=0; t<num_entries; t++)   /* normalized cond. probabilities */
    table.q[t] /= average_prob;
  
  /*for(t=0; t<num_entries; t++)
    printf("%d %e %d %d\n", t, table.q[t], table.a[t], table.b[t]); */

  return(table);
}

/******************* draw_number() *********************/
/** Draw discrete number using the Walkers method, as **/
/** implemented in K. Fuki and S. Todo, J. Comp. Phys.**/
/** 228 (2009) 2629-2642                              **/
/** PARAMETERS: (*)= return-paramter                  **/
/**    table: for drawing discrete random numbers     **/
/** RETURNS:                                          **/
/**      random number                                **/
/*******************************************************/
int draw_number(discrete_variate_t * table)
{
  int entry;
  entry = floor(drand48()*table->num_entries);
  if (drand48()<table->q[entry])
	  return(table->a[entry]);
  else
	  return(table->b[entry]);
}

int main(int argc, char *argv[])
{
  int histo[NUM_BINS];                                    /* histogram */
  int bin;
  double start_histo, end_histo;                 /* range of histogram */
  double delta;                                        /* width of bin */
  int t;                                               /* loop counter */
  int num_runs;                  /* number of generated random numbers */     
  double number;                                   /* generated number */
  double *p;                                 /* discrete probabilities */
  double sum;    /* for normalization */
  double mu;        /* parameter of Poisson distribution */
  discrete_variate_t table;

  sscanf(argv[1], "%lf", &mu);
  num_runs = atoi(argv[2]);                         /* read parameters */

  for(t=0; t<NUM_BINS; t++)                    /* initialise histogram */
      histo[t] = 0;        
  start_histo = -0.5; end_histo = NUM_BINS-0.5;
  delta = (end_histo - start_histo)/NUM_BINS; 
  
  p = (double *) malloc(NUM_BINS*sizeof(double));
  p[0] = exp(-mu);                  /* initialize Poisson distribution */
  sum = p[0];
  for(t=1; t<NUM_BINS; t++)
  {
    p[t] = mu*p[t-1]/t;
    sum += p[t];
  }
  for(t=0; t<NUM_BINS; t++)
  {
    p[t] /= sum;
  }
  table = setup_table(NUM_BINS, p);

  for(t=0; t<num_runs; t++)                               /* main loop */
  {
    number = draw_number(&table);    
    bin = (int) floor( (number-start_histo)/delta);
    histo[bin]++;
  }

  if(num_runs == 0)
    for(t=0; t<NUM_BINS; t++)
      printf("%d %e\n", t, p[t]);
  else
    for(t=0; t<NUM_BINS; t++)              /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	     histo[t]/(delta*num_runs));

  free(p);
  free(table.q);
  free(table.a);
  free(table.b);

  return(0);
}
