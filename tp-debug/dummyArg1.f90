    program dummyArg1
!
! number of arguments mismatch program
!
! Rewrite dummyArg1;f90 in Fortran 90 and use module/interface to 
! "prototype" foo.f so that the compiler can detect argument mismatch.
!
      implicit none
      integer i, n
      parameter (n=10)
      real A(n)
      data A/1.,2.,3.,4.,5.,6.,7.,8.,9.,10./

      write(*,*) A

      i = 2
      call foo(A,n)     ! missing third term "i"

    end program dummyArg1

      subroutine foo(A,n,i)
      implicit none
      integer n, i
      real A(n)

      write(*,*)'====> ',i,n,A(i)

    end subroutine foo
