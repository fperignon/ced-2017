module fft
  
  use, intrinsic :: iso_c_binding
  implicit none
  include 'fftw3.f03'

  contains

  subroutine init_fftw()
    type(C_PTR) :: plan
    complex(C_DOUBLE_COMPLEX), dimension(1024,1000) :: in, out
    print *, "start fftw ..."
    plan = fftw_plan_dft_2d(1000,1024, in,out, FFTW_FORWARD,FFTW_ESTIMATE)

  end subroutine init_fftw

end module fft
