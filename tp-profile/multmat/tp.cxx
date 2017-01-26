/* C source code is found in dgemm_example.c */

#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include "matmul.hpp"
#include <assert.h>
#include <iostream>

int main()
{
  printf ("\n This example computes real matrix C=alpha*A*B+beta*C using \n"
	  " Intel(R) MKL function dgemm, where A, B, and  C are matrices and \n"
	  " alpha and beta are double precision scalars\n\n");

  // Dimensions des matrices
  int m = 2000, k = 200, n = 1000;

  printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
	  " A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);

  // 
  printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
	  " performance \n\n");

  // Allocation mémoire pour les différentes matrices
  double * A = (double *)mkl_malloc( m*k*sizeof( double ), 64 );
  double * B = (double *)mkl_malloc( k*n*sizeof( double ), 64 );
  double * C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
  double * A2 = new double[m*k];
  double * B2 = new double[k*n];
  double * C2 = new double[m*n];
  
  if (A == NULL || B == NULL || C == NULL) {
    printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);
    return 1;
  }
  if (A2 == NULL || B2 == NULL || C2 == NULL) {
    printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
    delete(A2, B2, C2);
  }

  // Remplissage des matrices
  init_matrices(A, B, C, m, n, k);
  init_matrices(A2, B2, C2, m, n, k);
  // On vérifie qu'on traite bien 2 cas similaires
  double normA = cblas_dnrm2(k*m, A, 1);
  double normA2 = cblas_dnrm2(k*m, A2, 1);
  double normB = cblas_dnrm2(n*k, B, 1);
  double normB2 = cblas_dnrm2(n*k, B2, 1);
  double tol = 1e-14;
  assert (abs(normA-normA2) < tol);
  assert (abs(normB-normB2) < tol);

  // Calcul optimisé
  printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");
  mkl_matmul(A, B, C, m, n, k);
  printf ("\n Computations completed.\n\n");

  // Calcul naif
  printf (" Computing matrix product using naive product \n\n");
  matmul(A2, B2, C2, m, n, k);
  printf ("\n Computations completed.\n\n");
  // Verification des résultats
  double v1 = cblas_dnrm2(n*m, C, 1);
  double v2 = cblas_dnrm2(n*m, C2, 1);
  assert(abs(v2 - v1) < tol);

  // Calculs identiques mais dans des boucles, avec timers
  double s_initial,s_elapsed;
  int LOOP_COUNT = 10;

  s_initial = dsecnd();
  printf("dsecnd = %.5f milliseconds",s_initial);
  for (int r = 0; r < LOOP_COUNT; r++)
    {
      mkl_matmul(A, B, C, m, n, k);
    }
  s_elapsed = (dsecnd() - s_initial) / LOOP_COUNT;
  printf (" == Matrix multiplication using Intel(R) MKL dgemm completed == \n"
	  " == at %.5f milliseconds == \n\n", (s_elapsed * 1000));

  printf (" Measuring performance of matrix product using triple nested loop \n\n");
  s_initial = dsecnd();
  for (int r = 0; r < LOOP_COUNT; r++)
    {
      matmul(A2, B2, C2, m, n, k);
    }
  s_elapsed = (dsecnd() - s_initial) / LOOP_COUNT;
  printf (" == Matrix multiplication using triple nested loop completed == \n"
	  " == at %.5f milliseconds == \n\n", (s_elapsed * 1000));

  
  printf ("\n Deallocating memory \n\n");
  mkl_free(A);
  mkl_free(B);
  mkl_free(C);
  delete(A2, B2, C2);
  printf (" Example completed. \n\n");
  return 0;
}
