/**********************************************************/
/*** Simulation of diluted ferromagnet                  ***/
/***                                                    ***/
/*** Version 0.1.0.0                                    ***/
/***                                                    ***/
/*** A.K. Hartmann May 2005                             ***/
/***                                                    ***/
/**********************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "percol.h"

/* function commentary header (empty): */
// TODO: 1 Implement the function diluted_PT()
// NOTE: Take num_T configurations, the function performs for each configuration some sweeps of the Monte Carlo algorithm
//       by calling diluted_mc_T(). Afterwards num_T-1 times two neighboring configurations at T_k and T_{k+1} are attempted to be swapped.
//       Each time k ∈ {0, 1, ..., num_T-2} is chosen randomly. A full cycle is considered to be a step of the MC time.
//       The function also receives arrays exch[] and tries[] to count the number of successful swaps and the number of attempted swaps, at the k-th step.
//       This is used to calculate the acceptance rate of the swaps. (double) exch[k]/tries[k].
//       Hint 1: Inside diluted_PT(), you also need to call diluted_energy().
//       Hint 2: Exchange two configurations, by exchanging the corresponding two pointers stored in sping_cfg[]. DO not exchange all spin values.
/************************** diluted_PT() ***********************/
/** Does parallel tempering for diluted ferromagnet           **/
/** at num_T temperatures T_0<T_1<...T_{num_T-1}.             **/
/** NOTE: This implmentation is for maximum simplicity,       **/
/** hence, it will perform poorly                             **/
/** PARAMETERS: (*)= return-paramter                          **/
/**         num_T: number of temperatures                     **/
/**  (*) spin_cfg: num_T spin-configurations                  **/
/**         num_n: number of nodes  in lattice                **/
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
  int k, mc_steps = 1000; // Define the number of Monte Carlo steps
  double delta, r;

  // Perform Monte Carlo algorithm for each temperature configuration
  for (k = 0; k < num_T; k++) {
    diluted_mc_T(spin_cfg[k], num_n, N, next, e, mc_steps, T[k]);
  }

  // Attempt to swap neighboring configurations
  for (k = 0; k < num_T - 1; k++) {
    double E1 = diluted_energy(spin_cfg[k], num_n, N, next, e);
    double E2 = diluted_energy(spin_cfg[k+1], num_n, N, next, e);

    delta = (1.0/T[k] - 1.0/T[k+1]) * (E2 - E1); // difference in inverse temperatures by difference in energy
    r = r_0_1();  // random number in [0,1)

    // If delta < 0 or r < exp(-delta), accept the swap of the spin configurations using the Metropolis algorithm
    if (delta < 0 || r < exp(-delta)) { // Acceptance criteria. If the energy difference is negative or the random number is less than the Boltzmann factor, accept the swap
      short int *temp = spin_cfg[k];
      spin_cfg[k] = spin_cfg[k+1];
      spin_cfg[k+1] = temp;
      exch[k]++; // Increment the count of successful swaps
    }
    tries[k]++; // Increment the count of attempted swaps
  }
}


/****************** r_0_1() **************************/
/** Random number distributed  uniformly in [0,1)   **/
/** PARAMETERS: (*)= return-parameter               **/
/**                                                 **/
/** RETURNS:                                        **/
/**    random number                                **/
/*****************************************************/
double r_0_1()
{
  double value;
  do
    value = ((double)rand())/(RAND_MAX);
  while(value == 1.0);
  return(value);
}

/****************** diluted_energy() *************************/
/** Calculates energy of configuration                      **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**      num_n: number of neighbours                        **/
/**          N: number of spins                             **/
/**       next: gives neighbours next[0..N][0..num_n+1](t2)**/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     energy                                              **/
/*************************************************************/
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

/************************** diluted_print() ******************/
/** prints configuration line by line                       **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**          N: number of spins                             **/
/**       line: number of spins in one line                 **/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     nothing                                             **/
/*************************************************************/
void diluted_print(short int *spin, int N, int line, short int *e)
{
  int t;

  for(t=1; t<=N; t++)                       /* loop over all spins */
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

/****************** diluted_magnetisation() ******************/
/** Caluclates magnetisation of configuration               **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**          N: number of spins                             **/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     magnetization                                       **/
/*************************************************************/
double diluted_magnetisation(short int *spin, int N, short int *e)
{
  int t;
  double mag;

  mag = 0.0;
  for(t=1; t<=N; t++)                       /* loop over all spins */
    mag += spin[t]*e[t];                /* calculate magnetisation */
  return(mag);
}

/****************** diluted_mag_cluster() ********************/
/** Caluclates magnetisation of configuration just for spins**/
/** of given cluster 'cluster_id'                           **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**          N: number of spins                             **/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     magnetization                                       **/
/*************************************************************/
double diluted_mag_cluster(short int *spin, int N, short int *e, 
			   int *cluster, int cluster_id)
{
  int t;
  double mag;

  mag = 0.0;
  for(t=1; t<=N; t++)                       /* loop over all spins */
    if(cluster[t] == cluster_id)
      mag += spin[t]*e[t];                /* calculate magnetisation */
  return(mag);
}

/****************** diluted_mc_T() ***************************/
/** Does metropolis MC-simulation with diluted ferromagnet  **/
/** at T>0.                                                 **/
/** PARAMETERS: (*)= return-paramter                        **/
/**  (*)  spin: spin-configuration [1..N]                   **/
/**      num_n: number of neighbours in lattice             **/
/**          N: number of spins                             **/
/**       next: gives neighbours next[0..N][0..2*dim+1] (t2)**/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/**   mc_steps: number of MC steps                          **/
/**          T: temparture in units of j                    **/
/** RETURNS:                                                **/
/**     nothing                                             **/
/*************************************************************/
void diluted_mc_T(short int *spin, int num_n, int N, int *next, 
		 short int *e, int mc_steps, double T)
{
    int t,r, t2, num_mc;
    double delta_e;

    for(num_mc=0; num_mc<mc_steps*N; num_mc++)                    /* do MC */
    {
      double p;
      do
	t = 1+ (int) (r_0_1() * N);              /* choose spin randomly */
      while(e[t] == 0);
      delta_e = 0.0;
      for(r=0; r<num_n; r++)           /* calulate local energy -> delta_e */
      {
	t2 = NEXT(t,r);
	delta_e += 2.0*spin[t]*spin[t2]*e[t2];
      }
      p = r_0_1(); 
      if( (delta_e <= 0)||(p< exp(-delta_e/T) ))            /* flip spin ? */
      {
	spin[t]=-spin[t];                                     /* flip spin */
      }
    }
}



