/* C source code is found in dgemm_example.c */

#include <stdio.h>
#include <stdlib.h>
#include "matmul.hpp"
#include <assert.h>
#include <iostream>

int main()
{
  printf ("\n This example computes real matrix C=alpha*A*B+beta*C using \n"
	  " Intel(R) MKL function dgemm, where A, B, and  C are matrices and \n"
	  " alpha and beta are double precision scalars\n\n");

  // Dimensions des matrices
  int m = 200, k = 20, n = 100;

  // Allocation mémoire pour les différentes matrices

  double * A2 = new double[m*k];

  double * B2 = new double[k*n];
  double * C2 = new double[m*n];
  
  if (A2 == NULL || B2 == NULL || C2 == NULL) {
    printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
    delete(A2, B2, C2);
  }

  // Remplissage des matrices
    init_matrices(A2, B2, C2, m, n, k);
  
  // Calcul naif
  printf (" Computing matrix product using naive product \n\n");
  matmul(A2, B2, C2, m, n, k);
  printf ("\n Computations completed.\n\n");
  
  // Calculs identiques mais dans des boucles, avec timers
  double s_initial,s_elapsed;
  int LOOP_COUNT = 1;

  for (int r = 0; r < LOOP_COUNT; r++)
    {
      matmul(A2, B2, C2, m, n, k);
    }
    
  delete[](A2);
  delete[](B2);
  delete[](C2);
  printf (" Example completed. \n\n");
  return 0;
}
