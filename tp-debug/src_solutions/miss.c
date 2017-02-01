#include <stdio.h>

/* #if defined(__cplusplus) */
/* extern "C" */
/* #endif */
/* void foo_(float* A, int* n, int* i); */
#include "miss.h"

#define n 10

int main()
{
  int i;
  float A[n];
  int nn = n;
  for (i=0; i<n; i++) {
    A[i] = (float) i+1;
  }

  i = 2;
  foo(A, &nn, &i);

  return 0;
}


// Compilation:
// gfortran -c foo.f
// gcc -lgfortran foo.o miss2.c
// marche aussi avec g++ ou intel compilers (ifort + icc/icpc -lifcore)
