program main

use tools
use fft
implicit none

integer :: STATUS = 0
call init_fftw()

print *, 'This program is going to exit.'
call EXIT(STATUS)

end program main

