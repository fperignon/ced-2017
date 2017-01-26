PROGRAM dynamic 
  REAL,DIMENSION(:),ALLOCATABLE::mobile
  REAL,DIMENSION(12)::stiff
  INTEGER::total,addem
  stiff=(/(i,i=1,12)/)
  mobile=2*stiff
  total=SUM(stiff)
  print *,"total=",total
  addem=SUM(mobile)
  print *,"addem=",addem 
END PROGRAM dynamic
