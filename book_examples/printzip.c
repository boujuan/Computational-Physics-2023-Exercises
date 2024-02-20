/*******************************************************************/
/*** Examples for usage of program arguments and (un)zipping     ***/
/*** of input files (solution to exercise)                       ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Input/Output                                       ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char name_file[1000];                          /* name of input file */
  char *gzpos;                        /* position of ".gz" in filename */
  char command[1000];                            /* for system() calls */
  char line[1000];          /* string where one line of file is stored */
  FILE *file_in;                         /* file pointer to input file */
  int argz = 1;                          /* counter to treat arguments */


  if( (argc-argz) != 1)                      /* not enough arguments ? */
  {                                       /* print error/usage message */
    fprintf(stderr, "USAGE: %s <file>\n", argv[0]);
    exit(1);
  }

  strcpy(name_file, argv[argz++]);
  gzpos = strstr(name_file, ".gz");   /* find pos of ".gz" in filename */

  if(gzpos != 0)                                     /* is it zipped ? */
  {
    sprintf(command, "gzip -d %s", name_file);
    system(command);                                       /* unzip it */
    *gzpos = 0;                               /* remove trailing ".gz" */
  }

  file_in = fopen(name_file, "r");
  while(!feof(file_in))           /* read until end of file is reached */
  {
    if(fgets(line, 999, file_in) == NULL)              /* read in line */
      continue;                                 /* nothing was read in */
    printf("%s", line);                                /* print line */
  }

  fclose(file_in);                                       /* close file */
  if(gzpos != NULL)                             /* was it compressed ? */
  {
    sprintf(command, "gzip %s", name_file);
    system(command);                               /* compress it again */
  }
  return(0);
}
