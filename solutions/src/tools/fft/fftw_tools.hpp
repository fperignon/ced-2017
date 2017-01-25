/*
  fftw header
*/
#ifndef FFTW_TOOLS
#define FFTW_TOOLS
#include "tools_config.hpp"
#ifdef HAS_FFTW
#if defined(__cplusplus)
extern "C"
{
#endif
void apply_fftw();

#ifdef FLOAT_PREC
  void apply_fftwf();
#endif
  
#if defined(__cplusplus)
}
#endif
#endif
#endif
