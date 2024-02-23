/********************************************************/
/*** types etc for simulation of percolation          ***/
/*** A.H. Hartmann  24.4.2005                         ***/
/********************************************************/

#ifndef _DILUTED_H_
#define _DILUTED_H_

/** macros **/

/** types **/

/** prototypes **/

extern double r_0_1();
extern double diluted_energy(short int *spin, int num_n, int N, int *next, 
			     short int *e);
extern void diluted_print(short int *spin, int N, int line, short int *e);
extern double diluted_magnetisation(short int *spin, int N, short int *e);
extern double diluted_mag_cluster(short int *spin, int N, short int *e, 
				  int *cluster, int cluster_id);
extern int diluted_mc_T(short int *spin, int num_n, int N, int *next, 
			short int *e, int mc_steps, double T);


#endif /* ifdef diluted */
