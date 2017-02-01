module foomod

  use iso_c_binding

  implicit none

contains
  subroutine foo(A,n,i) bind(C)
   
    integer(C_INT), intent(in) :: n, i
    real(C_FLOAT), dimension(n), intent(in) :: A
    print *, i
    write(*,*)'====> ',i,n,A(i)
    
  end subroutine foo
end module foomod
