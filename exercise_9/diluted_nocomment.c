// Simulation of diluted ferromagnet
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "percol.h"
// TODO: 1 Implement the function diluted_PT()
/************************** diluted_PT() ***********************/
/** Does parallel tempering for diluted ferromagnet           **/
/** at num_T temperatures T_0<T_1<...T_{num_T-1}.             **/
/** NOTE: This implmentation is for maximum simplicity,       **/
/** hence, it will perform poorly                             **/
/** PARAMETERS: (*)= return-paramter                          **/
/**         num_T: number of temperatures                     **/
/**  (*) spin_cfg: num_T spin-configurations                  **/
/**         num_n: number of neighbours in lattice            **/
/**             N: number of spins                            **/
/**          next: gives neighbours next[0..N][0..2*num_n+1]  **/
/**             e: sites arre ocupied (e[i]=1),empty (=0 )    **/
/**             T: num_T temperatures in units of J           **/
/**      (*) exch: count accepted swaps T_k <-> T_{k+1}       **/
/**     (*) tries: count tried swaps T_k <-> T_{k+1}          **/
/** RETURNS:                                                  **/
/**         nothing                                           **/
/***************************************************************/
void diluted_PT(int num_T, short int **spin_cfg, int num_n, int N, int *next, short int *e, double *T, int *exch, int *tries)
{
  
}

double r_0_1()
{
  double value;
  do
    value = ((double)rand())/(RAND_MAX);
  while(value == 1.0);
  return(value);
}

double diluted_energy(short int *spin, int num_n, int N, int *next, 
		 short int *e)
{
  int t,r;
  double energy;

  energy = 0.0;
  for(t=1; t<=N; t++)                            /* loop over all spins */
    if(e[t] != 0)
      for(r=0; r<num_n; r++)                        /* calulate energy */
	energy += -spin[t]*spin[NEXT(t, r)]*e[NEXT(t,r)];
  return(energy/2.0);
}

void diluted_print(short int *spin, int N, int line, short int *e)
{
  int t;

  for(t=1; t<=N; t++)                       
  {
    if(e[t] == 0)
      printf(" ");
    else if(spin[t]==1)
      printf("X");
    else
      printf("-");
    if(t%line == 0)
      printf("\n");
  }
}

double diluted_magnetisation(short int *spin, int N, short int *e)
{
  int t;
  double mag;

  mag = 0.0;
  for(t=1; t<=N; t++)                       
    mag += spin[t]*e[t];                
  return(mag);
}

double diluted_mag_cluster(short int *spin, int N, short int *e, 
			   int *cluster, int cluster_id)
{
  int t;
  double mag;

  mag = 0.0;
  for(t=1; t<=N; t++)                       
    if(cluster[t] == cluster_id)
      mag += spin[t]*e[t];                
  return(mag);
}

void diluted_mc_T(short int *spin, int num_n, int N, int *next, 
		 short int *e, int mc_steps, double T)
{
    int t,r, t2, num_mc;
    double delta_e;

    for(num_mc=0; num_mc<mc_steps*N; num_mc++)                    
    {
      double p;
      do
	t = 1+ (int) (r_0_1() * N);              
      while(e[t] == 0);
      delta_e = 0.0;
      for(r=0; r<num_n; r++)           
      {
	t2 = NEXT(t,r);
	delta_e += 2.0*spin[t]*spin[t2]*e[t2];
      }
      p = r_0_1(); 
      if( (delta_e <= 0)||(p< exp(-delta_e/T) ))            
      {
	spin[t]=-spin[t];                                     
      }
    }
}
