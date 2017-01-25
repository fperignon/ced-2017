#ifndef MKL_INTERFACE
#define MKL_INTERFACE
#include "tools_config.hpp"

#ifdef HAS_MKL
#include "mkl_lapacke.h"

#if defined(__cplusplus)
extern "C"
{
#endif
void apply_mkl();
void print_matrix( char* desc, MKL_INT m, MKL_INT n, double* a, MKL_INT lda );
void print_int_vector( char* desc, MKL_INT n, MKL_INT* a );


#if defined(__cplusplus)
}
#endif
#endif
#endif
