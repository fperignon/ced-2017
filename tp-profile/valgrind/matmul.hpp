#ifndef MAT_INTERFACE
#define MAT_INTERFACE

#if defined(__cplusplus)
extern "C"
{
#endif

  void init_matrices(double * A, double* B, double * C, int m, int n, int k);
  void matmul(double * A, double* B, double * C, int m, int n, int k);
  void print_mat(char* desc, int m, int n, double* a, int lda );


#if defined(__cplusplus)
}
#endif
#endif

