      subroutine foo(A,n,i)
      implicit none
      integer n, i
      real A(n)

      write(*,*)'i, n, A(i) in foo : ',i,n,A(i)

      end
