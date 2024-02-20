This directory contains sample and solution programs from
the chapter "Programming in C" of the book
A.K. Hartmann "A practical guide to computer simulations" 
(World Scientific, 2008)


First program:
--------------
Prints out a message
SOURCES:
  first.c 
COMPILE:
  cc -o first first.c -Wall
RUN:
  first


address of variable:
--------------------
SOURCES:
  address.c
COMPILE:
  cc -o address address.c -Wall
RUN:
  address


size of data types:
-------------------
Prints number of bytes used for differen data types
SOURCES:
  sizeof.c
COMPILE:
  cc -o sizeof sizeof.c -Wall
RUN:
  sizeof


increment operators:
--------------------
shows the usage of pre/post in/decrement operators
SOURCES:
  increment.c
COMPILE:
  cc -o increment increment.c -Wall
RUN:
  increment


mathematical functions:
-----------------------
shows usage of some standard mathematical functions
SOURCES:
  mathtest.c  
COMPILE:
  cc -o mathtest mathtest.c -lm -Wall
RUN:
  mathtest


structures:
-----------
shows the usage of structures to assemble data types
SOURCES:
  person.c 
COMPILE:
  cc -o person person.c -Wall 
RUN:
  person


functions:
----------
shows how to define function, example of step function, where
a table of function values is printed
SOURCES:
  step_fct.c
COMPILE:
  cc -o step_fct step_fct.c -Wall
RUN:
  step_fct

  
functions (2):
--------------
To teach more complex functions, e.g. with struct as return type
or how to use pointers to return values.
Contains the functions minmax() and minmax2(), which calculate the smallest
and the largest elements of an array.
SOURCES:
  min_max.c
COMPILE:
  cc -o min_max min_max.c -lm -Wall
RUN:
  min_max


static variables:
-----------------
a static variable is used to count how often a function was called
SOURCES:
  static.c 
COMPILE:
  cc -o static static.c -Wall
RUN:
  static


scope of variables:
-------------------
shows how the definition of local variables can hide global variables
SOURCES:
  hide.c
COMPILE:
  cc -o hide hide.c -Wall
RUN:
   hide


printing:  
---------
shows usage of printf
SOURCES:
  printing.c 
COMPILE:
  cc -o printing printing.c -Wall
RUN:
  printing 


writing to files:
-----------------
Creates a file "sin.dat" where a table of values of the sin(x)
function in the range [0,2*PI] is written to.
SOURCES:
  file_o.c
COMPILE:
  cc -o file_o file_o.c -lm -Wall  
RUN: 
  file_o
  

Read in data files:
-------------------
Reads in a four column data file, while ignoring all comment (#)
lines. As ty example the sum of columns 2,3,4 is printed.
SOURCES:
  file_in.c
COMPILE:
  cc -o file_in file_in.c -lm  -Wall
RUN:
  file_in


Treatment of program arguments, options and zipping of output files:
--------------------------------------------------------------------
What every simulation program should do:
For an imaginary simulation program, some options are treated, the
number of arguments is checked. If the number is wrong an error
massage (usable a simple help function) is printed. Else two arguments
are read in. An output file is created. First, the calling line and 
some program parameters are written to the file.
After the output files is closed, it is compressed automatically.
SOURCES:
  arguments.c
COMPILE:
  cc -o arguments arguments.c  -Wall
RUN:
  arguments {options} <size> <temperature>


defining structs and their memory usage
---------------------------------------
(solution to exercise)
Sets up a simple data structure and calculates it size
SOURCES:
  struct_size.c
COMPILE:
  cc -o struct_size struct_size.c -Wall
RUN:
  struct_size


Pointer juggling/ addresses of addresses:
------------------------------------------
(solution to exercise)
Shows how to use pointers and pointers to pointers
SOURCES:
  pointers.c
COMPILE:
  cc -o pointers pointers.c -Wall  
RUN:
  pointers


permutation matrix: 
------------------
(solution to exercise)
Defines a permutation matrix which exchanges neighboring rows,
 applies it to a test matrix and prints the result.
SOURCES:
  matrix.c
COMPILE:
  cc -o -o matrix matrix.c -Wall
RUN:
  matrix


online unzipping: 
------------------
(solution to exercise)
prints file which is passed. If file is compressed, it is uncompressed first,
and compressed after printing.

SOURCES:
  printzip.c
COMPILE:
  cc -o -o printzip printzip.c -Wall
RUN:
  printzip


Bisection search
----------------
(solution to exercise)
Searches an array of sorted integers via bisection search
SOURCES:
  bisection.c
COMPILE:
  cc -o bisection bisection.c -Wall
RUN:
  bisection


Integration of function
-----------------------
(solution to exercise)
Integrates a function by simply approximating it by a sum 
SOURCES:
  integrate.c
COMPILE:
  cc -o integrate integrate.c -lm -Wall
RUN:
  integrate


Test compiler optimization:
---------------------------
(solution to exercise)
Calculates sums of numbers over all possible subsets for set of numbers.
Should be compiled with different levels of optimization -O0, -O1,
-O2, -O3. The running time should be measured using 'time'
SOURCES:
  optimization.c
COMPILE:
  cc -o optimization optimization.c -lm -Ox -Wall
RUN:
  time optimization
