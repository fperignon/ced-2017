program trapezoid

! integrate sin(x) over the interval 0 to pi
! using trapezoid rule

implicit none

integer :: i, n = 11, nm
real :: pi, f1, f2, x1, x2, xint

write(*, "('  i        x       f(x)    int(f(x))'/&

          &'  1      0.00      1.00      0.00' )" )

pi = acos(-1.0)
nm = n-1
xint = 0.0
x1 = 0.0

do i = 2, n
   x2 = ((i-1)/nm)*pi
   f1 = cos(x1)
   f2 = cos(x2)
   xint = xint + 0.5*(f1+f2)*(x2-x1)
   x1 = x2

   write(*, '(i3, 3(f10.2))') i, x2, f2, xint

enddo

end program trapezoid
