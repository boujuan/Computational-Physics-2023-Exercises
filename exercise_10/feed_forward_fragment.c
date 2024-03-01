#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/********************* output_neuron2() *****************/
/** Calculates output of one McCullo-Pitts Neuron with **/
/** 'Fermi' function' for                              **/
/** given input x and weights w (threshold 0)          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of input values               **/
/**            x: input                                **/
/**            w: weight vector                        **/
/** RETURNS:                                           **/
/**     neuron output (in [0,1])                       **/
/********************************************************/
double output_neuron2(int L, double *x, double *w)
{
  double sum = 0.0;
  int t;
  
  for(t=0; t<=L; t++)
    sum += w[t]*x[t];

  return(1.0/(1+exp(-sum)));
}

// TODO: 1 Complete this function
// INFO: x_0 and y_0 must be assigned. Utilise the function output_neuron2()
// This function calculates output of entire feed-forward network.
/********************* output_ff_network() **************/
/** Calculates output of feed-froward network (one     **/
/** hidden layer given input x and weights w,wt        **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of input values               **/
/**            x: input                                **/
/**            M: size of hidden layer                 **/
/**        (*) y: hidden layer neurons                 **/
/**            w: weight matrix input->hidden          **/
/**           wt: weight vector hidden->output         **/
/** RETURNS:                                           **/
/**     network output (in [0,1])                      **/
/********************************************************/
double output_ff_network(int L, double *x, int M, double *y, double **w, double *wt)
{
  int t;
  double z;

  //INFO: this should sum the output of the hidden layer neurons
  for(t=1; t<=M; t++)
    y[t] = output_neuron2(L, x, w[t]);

  // Final output neuron calculation (z) with the hidden layer output as input (y)
  z = output_neuron2(M, y, wt);

  return(z);
}
/******************* random_vector_d() ******************/
/** Generates a random 0/1 vector 'x' of length 'L'    **/
/** for entries (1..L), entry 0 is 1                   **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**        (*) x: vector                               **/
/** RETURNS:                                           **/
/**     (nothing)                                      **/
/********************************************************/
void random_vector_d(int L, double *x)
{
  int t;

  x[0] = 1;
  for(t=1; t<=L; t++)
    if(drand48()<0.5)
      x[t] = 0;
    else
      x[t] = 1;
}
/******************* test_majority_d() ******************/
/** Test for 0/1 vector 'x' of length 'L' whether      **/
/** more than half of the bits of 1..L are 1.          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**            x: vector                               **/
/** RETURNS:                                           **/
/**     1 if number of 1bits >= L/2, 0 else            **/
/********************************************************/
int test_majority_d(int L, double *x)
{ 
  int t;
  int counter = 0;

  for(t=1; t<=L; t++)
    if(x[t] != 0)
      counter++;

  if(counter > L/2)
    return(1);
  else
    return(0);

}
/********************* test_parity_d() ******************/
/** Test for 0/1 vector 'x' of length 'L' whether      **/
/** the number of 1 bits of 1..L is odd.               **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of values                     **/
/**            x: vector                               **/
/** RETURNS:                                           **/
/**     1 if number of 1bits  is odd                   **/
/********************************************************/
int test_parity_d(int L, double *x)
{ 
  int t;
  int counter = 0;

  for(t=1; t<=L; t++)
    if(x[t] != 0)
      counter++;

  return(counter %2);
}
// TODO: 2 Complete this function
// INFO: Adjust the weights w_ij, w~j, by iterating loop K times.
//       Each loop, generate random vectors (x_1,...,x_L) e {0,1}^L by calling
//       random_vector_d(). Obtain net output by output_ff_network().
//       Obtain target output by f(). Adjust the weights as in lecture.
//       Hint: recalculate network output after w~j is updated. (obtain new values for z).
//             Have to allocate corresponding vectors locally and free them before return.
/************************* ff_learning() ****************/
/** Performs 'K' steps of learning algorithm:          **/
/** generate random vector and adjust weights using    **/
/** parameter 'epsilon' to learn function 'f'          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of (real) values              **/
/**            M: number of hidden neuron              **/
/**        (*) w: weight matrix input ->hidden         **/
/**       (*) wt: weight vector hidden->output         **/
/**      epsilon: learning rate                        **/
/**            f: target function                      **/
/**            K: number of iterations                 **/
/** RETURNS:                                           **/
/**     (nothing)                                      **/
/********************************************************/
void ff_learning(int L, int M, double **w, double *wt, double epsilon, int (*f)(int, double *), int K )
{
  int step, t ,t2;                                 /* loop counters */
  double *x;                                       /* input vector */
  double *y;                              /* hidden neurons vector */
  double z, z_wanted;                             /* output values */

  // Allocate memory for x and y
  x = (double *) malloc( (L+1)*sizeof(double));
  y = (double *) malloc( (M+1)*sizeof(double));
  // INFO: x_0 and y_0 must be assigned to 1 because of the threshold
  x[0] = 1;
  y[0] = 1;

  // Main learning loop, iterate K times
  for(step=0; step<K; step++)
  {
    random_vector_d(L, x); // INFO: Generate random vector x of length L for entries (1..L), entry 0 is 1
    z = output_ff_network(L, x, M, y, w, wt); // Calculate the output of the network
    z_wanted = f(L, x); // target output (what we want to achieve)

    // INFO: Adjust the weights w_ij, w~j using gradient descent
    for(t=0; t<=M; t++)
    {
      // INFO: Update the weights w~j, this is for the output layer
      // (z - z_wanted) is the error
      // y[t] is the output of the hidden layer
      // y[t] * (1 - y[t]) is the derivative of the sigmoid function
      // Backpropagation of the weights from the output layer to the hidden layer
      wt[t] -= epsilon * (z - z_wanted) * y[t] * z * (1 - z);

      // z = output_ff_network(L,x, M, y, w, wt);

      for(t2=0; t2<=L; t2++)
      {
        // INFO: Update the weights w_ij by gradient descent and mean squared error
        // This is to update the weights from the input layer to the hidden layer
        // x[t2] is the input
        // wt[t] is the weight from the hidden layer to the output layer
        // y[t] is the output of the hidden layer
        // (z - z_wanted) is the error
        // y[t] * (1 - y[t]) is the derivative of the sigmoid function
        w[t][t2] -= epsilon * (z - z_wanted) * wt[t] * y[t] * (1 - y[t]) * x[t2];
      }
    }
  }
  // Free the allocated memory
  free(x);
  free(y);
}
/************************* ff_testing() *****************/
/** Peforms 'K' steps of ff algorithm:                 **/
/** generate random vector and evaluate network and    **/
/** compare with  function 'f'                         **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            L: number of (real) values              **/
/**            M: number of hidden neuron              **/
/**        (*) w: weight matrix input ->hidden         **/
/**       (*) wt: weight vector hidden->output         **/
/**      epsilon: learning rate                        **/
/**            f: target function                      **/
/**            K: number of iterations                 **/
/** RETURNS:                                           **/
/**     error rate                                     **/
/********************************************************/
double ff_testing(int L, int M, double **w, double *wt, 
			 int (*f)(int, double *), int K )
{
  int step;                                 /* loop counters */
  double *x;                                       /* input vector */
  double *y;                              /* hidden neurons vector */
  double z, z_wanted;                             /* output values */
  double deviation = 0;

  x = (double *) malloc( (L+1)*sizeof(double));
  y = (double *) malloc( (M+1)*sizeof(double));
  x[0] = 1;                              /* bit 0 <-> threshold */
  y[0] = 1;
  for(step=0; step<K; step++)             /* main learning loop */
  {
    random_vector_d(L, x);
    z = output_ff_network(L, x, M, y, w, wt);
    z_wanted = f(L, x);
    deviation += fabs(z-z_wanted);
  }
  free(x);
  free(y);

  return(deviation/K);
}

int main(int argc, char **argv) // Input arguments: L, M, maxrun, seed (optional)
{
  int L;                                         /* number of input bits */
  int M;                                     /* number of hidden neurons */
  double **w;                        /* weight vector input -> first layer */
  double *wt;                       /* weight vector first layer -> output */
  double epsilon;                                         /* learning rate */
  int run, t, t2;                                         /* loop counters */
  int maxrun;           // number of iterations for learning algorithm
  int argz = 1;                         /* to treat command-line arguments */
  int seed = 1000;
  int (*function)(int, double*);                  /*function to be learned */
  function = test_parity_d;
  // function = test_majority_d;

  L = atoi(argv[argz++]);
  M = atoi(argv[argz++]);
  maxrun = atoi(argv[argz++]);
  if(argz< argc)                                          /* optional seed */
    seed = atoi(argv[argz++]);
  srand48(seed);

  w = (double **) malloc((M+1)*sizeof(double *));       /* allocate memory */
  for(t=0; t<=M; t++)
  {
    w[t] = (double *) malloc((L+1)*sizeof(double));
    for(t2=0; t2<=L; t2++)
      w[t][t2] = 1*(drand48()-0.5);       // TODO: Random initialisation of the weight
  }
  wt = (double *) malloc((M+1)*sizeof(double));
  for(t=0; t<=M; t++)
    wt[t] = (drand48()-0.5); // INFO: Random initial weights [-0.5, 0.5] for w_ij, w~j

  epsilon = 1.0; // INFO: Learning rate

  for(run=0; run<maxrun; run++)              /* perform iterative learning */
  {
    if(run %100 == 0)
    {
      printf("%d %f\n", run, ff_testing(L, M, w, wt, function, 1000));
    }
    ff_learning(L, M, w, wt, epsilon, function, 1);
  }

  for(t=0; t<=M; t++)                           /* print resulting network */
  {
    printf("# ");
    for(t2=0; t2<=L; t2++)
      printf("w[%d][%d]=%f, ", t, t2, w[t][t2]);
    printf("\n");
  }
  for(t=0; t<=M; t++)
    printf("# wt[%d]=%f, ", t, wt[t]);
  printf("\n");

  for(t=0; t<=M; t++)                        /* give back allocated memory */
    free(w[t]);
  free(w);
  free(wt);
  return(0);
}