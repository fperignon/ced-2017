!> Description du module 
!!
!! on peut aussi mettre du latex: 
!! 	\f[
!!	g(\dot x, x, t, z) = 0
!!	\f]
module tools
implicit none

!> Une variable globale
integer, parameter :: var = 8

contains
  !> Description de test fortran
  !! \param val un entier
  subroutine affiche(val)
    real(kind=8) :: val 
    print *, "Appel de la routine affiche en fortran"
  end subroutine affiche
end module tools
