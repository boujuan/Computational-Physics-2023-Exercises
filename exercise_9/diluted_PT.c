#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "diluted.h"

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