/*******************************************************************/
/*** Advanced example for using data types:                      ***/
/*** Definition of a structure                                   ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Complex data types                                 ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  struct person
  {
    int          age; /* age of person (years) */
    double    height; /* height of person in meters */
    short int    sex; /* 0=male, 1=female */
    short int status; /* 0=single,1=married,2=divorced,3=widowed*/
    int         city; /* cities are coded as integers 1,... */
  };

  typedef struct person person_t;

  person_t p1, p2;

  int num_persons = 100;
  struct person pers[num_persons];
  int p;

  for(p=0; p<num_persons; p++)
    pers[p].status = 0;

  p1.age = 43;
  p1.height = 1.73;
  p1.sex = 0;
  p1.status = 0;
  p1.city = 23;

  p2 = p1;

  printf("The person has age %d\n", p2.age);

  return(0);
}
