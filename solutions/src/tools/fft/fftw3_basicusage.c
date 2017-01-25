/*--------------------------------------
 Exemple d'utilisation de la librairie FFTW

 FFT 1D, complexe
 -----------------------------------------*/
#include "fftw_tools.hpp"
#ifdef HAS_FFTW
#include<fftw3.h>

void apply_fftw()
{
  printf("FFTW double precision\n");
  // Nombre de points dans la grille.
  int N = 16;
  // Les données : tableaux de complexes en double precision
  fftw_complex *in, *out;
  // Allocation de la mémoire pour les données in/out de la fftw
  in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
  // Description du 'plan' (un objet qui contient toutes les infos nécessaires au calcul de la fft)
  fftw_plan my_plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  // init. in
  // ...
  // Calcul de out = fft(in)
  fftw_execute(my_plan);
  // Libération de la mémoire
  fftw_destroy_plan(my_plan);
  fftw_free(in);
  fftw_free(out);
}

#ifdef FLOAT_PREC
void apply_fftwf()
{
  printf("FFTW simple precision\n");
  // Nombre de points dans la grille.
  int N = 16;
  // Les données : tableaux de complexes en double precision
  fftwf_complex *in, *out;
  // Allocation de la mémoire pour les données in/out de la fftw
  in = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex)*N);
  out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex)*N);
  // Description du 'plan' (un objet qui contient toutes les infos nécessaires au calcul de la fft)
  fftwf_plan my_plan = fftwf_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  // init. in
  // ...
  // Calcul de out = fft(in)
  fftwf_execute(my_plan);
  // Libération de la mémoire
  fftwf_destroy_plan(my_plan);
  fftwf_free(in);
  fftwf_free(out);
}
#endif
#endif
