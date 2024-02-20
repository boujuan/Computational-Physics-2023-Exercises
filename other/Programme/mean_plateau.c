
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************* depose() *****************/
/** Put one particle in one randomly chosen  **/
/** column of a one-dimensional surface      **/
/** uses periodic boundary conditions        **/
/** PARAMETERS: (*)= return-paramter         **/
/**       size: of system                    **/
/** (*) height: 1d surface                   **/
/**  num_steps: num of deposed particles     **/
/** RETURNS:                                 **/
/**    nothing                               **/
/**********************************************/

struct analyse
{
double mean; /* mean height */
double roughness; /* roughness */
};

void depose(int size, int *height, int num_steps)
{
  int column, left, right,t;
  for(t=0; t<num_steps; t++)
  {
    column = (int) (size*drand48());                   /* choose column */
    height[column]++;
    if(column==0)                                 /* at left boundary ? */
      left = size-1;
    else
      left=column-1;
    if(column==(size-1))                         /* at right boundary ? */
      right=0;
    else
      right=column+1;
    if(height[left]>height[column])          /* stic particle to left ? */
      height[column]=height[left];
    if(height[right]>height[column])        /* stic particle to right ? */
      height[column]=height[right];
  }
}

struct analyse analysis(int size, int *height)
{
	int counter;
	double sum;
	double sum2;
	struct analyse mean_roughness1;
	
	sum = 0.0;
	sum2 = 0.0;
	for(counter=0; counter<size; counter++)
	{
		sum += height[counter];
		sum2 += (height[counter])*(height[counter]); 
	}
	mean_roughness1.mean = sum/size;
	mean_roughness1.roughness = sqrt(sum2/size-mean_roughness1.mean*mean_roughness1.mean);
	return(mean_roughness1);
}

int main(int argc, char **argv)
{
  int *height;
  int argz = 1;                                  /* for treating arguments */
  double *m, *m2, *w, *w2;
  int t, step, run, size=10;
  int num_iterations=100;                          /* num of swees per run */
  int num_runs=1000;                         /* number of independent runs */

  size = atoi(argv[argz++]);                             /* read arguments */
  num_iterations = atoi(argv[argz++]);
  num_runs = atoi(argv[argz++]);

  height= (int *) malloc(size*sizeof(int));             /* allocate system */
  m = (double *) malloc(num_iterations*sizeof(double));
  w = (double *) malloc(num_iterations*sizeof(double));
  m2 = (double *) malloc(num_iterations*sizeof(double));
  w2 = (double *) malloc(num_iterations*sizeof(double));
  
  struct analyse mean_roughness;
  
  for(t=0; t<num_iterations; t++)
  {
    m[t] = 0;
    m2[t] = 0;
    w[t] = 0;
    w2[t] = 0;
  }
  
  double *mean_plateau;
  mean_plateau = (double *) malloc(size/50*sizeof(double));
  
  int size_;
  for(size_=50; size_<size;)
  {
	  for(run=0; run<num_runs; run++)      /* make 'num_runs' independent runs */
	  {
	    for(t=0; t<size_; t++)                            /* initialise surface */
	      height[t]=0;

	    for(step=0; step<num_iterations; step++)                  /* do sweeps */
	    { 
	      depose(size_, height, size_);
      
	      /******** INSERT THE CALL TO FUNCTION analysis() here *******/
	  
		  mean_roughness = analysis(size, height);
	  
	      m[step] += mean_roughness.mean /****** ADD MEAN ******/ ;   
	      m2[step] += mean_roughness.mean*mean_roughness.mean /****** ADD MEAN*MEAN ******/;
	      w[step] += mean_roughness.roughness /****** ADD ROUGHNESS ******/;
	      w2[step] += mean_roughness.roughness*mean_roughness.roughness /****** ADD ROUGHNESS*ROUGHNESS ******/ ;
	    }
	  }
  	
	  double sum;
	  int number;
	  int counter;
	  sum = 0.0;
	  number = 100;
	  
	  for(counter=num_iterations-100; counter<num_iterations; counter++)
	  		sum += w[counter]/num_runs;
	  mean_plateau[size_/50-1] = sum/number;
		  /* print results */
	  printf("%d %f\n", size_, mean_plateau[size_/50-1]);
	  
	  size_ += 50;
  }

  free(mean_plateau); free(height); free(m); free(w); free(m2); free(w2);

  return(0);
}
