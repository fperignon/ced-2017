#include <stdio.h>

/* number of arguments mismatch program. */

/* Modify dummyArg1.c to prototype function foo so that the compiler 
   can detect argument mismatch */

/* void foo(float* A, int* n, int* i); */  /* no prototyping */

#define n 10

int main()
{
  int i;
  float A[n];

  for (i=0; i<n; i++) {
    A[i] = (float) i+1;
  }

  i = 2;
  foo(A, n);   /* missing the third argument */

  return 0;
}


foo.c

void foo(float* A, int n, int i) {
  printf("====> %d, %d, %f\n", i, n, A[i]);
}
