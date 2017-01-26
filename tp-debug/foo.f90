subroutine foo(A,n,i)
  
  integer, intent(in) :: n, i
  real, dimension(n), intent(in) :: A
  print *, i
  write(*,*)'====> ',i,n,A(i)
    
end subroutine foo

