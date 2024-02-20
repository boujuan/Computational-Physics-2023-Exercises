/*******************************************************************/
/*** Examples for how to read in parameters using program        ***/
/*** arguments:                                                  ***/
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


int main(int argc, char *argv[])
{
  char name_outfile[1000];            /* name of output file */
  char appendix[1000];            /* to identify output file */
  char command[1000];                  /* for system() calls */
  FILE *file_out;             /* file pointer to output file */
  double temp;                                /* temperature */
  int do_save;                /* save files at end of output */
  int print_help;                    /* print help message ? */
  double l;                        /* lateral size of system */
  int N;                              /* number of particles */
  int num_steps;          /* how many MD steps are performed */
  int argz = 1;                /* counter to treat arguments */
  int t;                                     /* loop counter */

  /** default values **/
  l = 10; do_save = 0; appendix[0] = 0; 
  num_steps = 10000; print_help = 0;

  /** treat command line arguments **/
  while((argz<argc)&&(argv[argz][0] == '-'))
  {
    if(strcmp(argv[argz], "-steps") == 0)
      num_steps = atoi(argv[++argz]);
    else if(strcmp(argv[argz], "-save") == 0)
      do_save = 1;
    else if(strcmp(argv[argz], "-size") == 0)
      sscanf(argv[++argz], "%lf", &l);
    else if(strcmp(argv[argz], "-appendix") == 0)
      strcpy(appendix, argv[++argz]);
    else
    {
      fprintf(stderr, "unkown option: %s\n", argv[argz]);
      print_help = 1;
      break;
    }
    argz++;
  }

  if( print_help || (argc-argz) != 2)  /* not enough arguments ? */
  {                                 /* print error/usage message */
    fprintf(stderr, "USAGE: %s {<options>} <num_part> <temp>\n", 
	    argv[0]);
    fprintf(stderr, "   options: -steps <n> : num. MD steps "
	    "(d:%d)\n",  num_steps);
    fprintf(stderr, "     -size <l>: system size (d:%d)\n", 
	    l);
    fprintf(stderr, "     -save: save config at end\n");
    fprintf(stderr, "     -appendix <s>: for output file name\n");
    exit(1);
  }

  N = atoi(argv[argz++]);             /* read standard arguments */
  sscanf(argv[argz++], "%lf", &temp);

  sprintf(name_outfile, "md_N%d_T%3.2f%s.out",      /* file name */
	  N, temp, appendix);
  file_out = fopen(name_outfile, "w");
  
  fprintf(file_out, "# calling sequence: ");       /* print args */
  for(t=0; t<argc; t++)          /* print command line arguments */
    fprintf(file_out,"%s ", argv[t]);
  fprintf(file_out, "\n");  
  fprintf(file_out, "# params: num_steps=%d, size=%f, save=%d\n",
	  num_steps, l, do_save);

  fclose(file_out);                                /* close file */
  sprintf(command, "gzip %s", name_outfile);         /* zip file */
  system(command);

  return(0);
}
