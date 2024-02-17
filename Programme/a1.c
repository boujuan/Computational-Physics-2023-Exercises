#include <stdio.h>

void log_function(double a)
{
  double x;
  int counter;
  x = 0.5;
  for(counter=0; counter<400; counter=counter+1)
  {
    x = a * x * (1 - x);
    if (counter >= 100)
    {
      printf("%f, %f\n", a, x);
    }
  }
}

int main()
{
  double counter;
  for(counter=2.8; counter<4.0; counter=counter+0.01)
  {
    log_function(counter);
  }
  return(0);
}
