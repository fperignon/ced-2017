#include <stdio.h>

#define n 10
// void foo_(float * ,int *, int *);

int main()
{
  int i;
  double A[n];

  for (i=0; i<n; i++) {
    A[i] = (double) i+1;
  }

  i = 2;
  foo_(A, n);

  return 0;
}
