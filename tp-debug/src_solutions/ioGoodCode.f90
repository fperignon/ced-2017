PROGRAM sections
 
TYPE idrecord 
      INTEGER id 
      CHARACTER(len=16) :: name
      CHARACTER(len=3)  :: country
      INTEGER rating
      CHARACTER(len=2)  :: title 
      INTEGER experience
END TYPE idrecord

!INTEGER,PARAMETER :: Nplayer=10
integer, PARAMETER :: Nplayer=8

TYPE(idrecord) test(Nplayer)


OPEN(UNIT=10,FILE="sectionsCT.txt",status="OLD")

OPEN(UNIT=11,FILE="out.data",FORM='unformatted')

DO I=1,Nplayer
   READ(10,FMT='(I6,TR1,A14,A3,TR3,I4,TR3,A2,TR3,I3)')test(I)
   IF(test(I)%experience .LT. 30) THEN
      test(I)%experience=0
   ELSE IF (test(I)%experience.LT.100) then
      test(I)%experience=1
   ELSE
      test(I)%experience=2
  END IF
  WRITE(11)test(I)
END DO

CLOSE(UNIT=10)
CLOSE(UNIT=11)

OPEN(UNIT=20,FILE="out.data",FORM='unformatted')
OPEN(UNIT=21,FILE="final.data",STATUS='new')

DO I=1,Nplayer
   READ(20)test(I)
   IF(test(I)%title .EQ. "U")THEN
      test(I)%title=" "
   END IF

   WRITE(21,FMT='(A2,A,A16,I3)')test(I)%title," ",test(I)%name, &
        test(I)%rating
END DO

CLOSE(UNIT=20)
CLOSE(UNIT=21)

END PROGRAM sections

