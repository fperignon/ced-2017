program miss1

  implicit none
  
  integer :: i
  integer, parameter :: n=10
  real, dimension(n) ::  A
  data A/1.,2.,3.,4.,5.,6.,7.,8.,9.,10./

  write(*,*) A

  i = 2
  call foo(A,n)

end program miss1
