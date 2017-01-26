#include "matmul.hpp"
#include <stdio.h>
#include <assert.h>

void init_matrices(double * A, double* B, double * C, int m, int n, int k)
{
  printf (" Intializing matrix data \n\n");
  assert(A != NULL);
  assert(B != NULL);
  assert(C != NULL);
  for (int i = 0; i < (m*k); i++) {
    A[i] = (double)(i+1);
  }
  
  for (int i = 0; i < (k*n); i++) {
    B[i] = (double)(-i-1);
  }
  
  for (int i = 0; i < (m*n); i++) {
    C[i] = 0.0;
  }
}

void matmul(double * A, double* B, double * C, int m, int n, int k)
{
  assert(A != NULL);
  assert(B != NULL);
  assert(C != NULL);
  double sum;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      sum = 0.0;
      for (int l = 0; l < k; l++)
	sum += A[k*i+l] * B[n*l+j];
      C[n*i+j] = sum;
    }
  }
}

/* Auxiliary routine: printing a matrix */
void print_mat(char* desc, int m, int n, double* a, int lda )
{
  printf( "\n %s\n", desc );
  for( int i = 0; i < m; i++ )
    {
      for(int j = 0; j < n; j++ )
	printf( " %6.2f", a[i*lda+j] );
      printf( "\n" );
  }
}

