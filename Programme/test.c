#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n, n1, n2;
  n = atoi(argv[1]); 
  
  n1 = n/2; n2 = n-n1;
  printf("n1 = %d\n", n1);
  printf("n2 = %d\n", n2);

  return(0);
}
