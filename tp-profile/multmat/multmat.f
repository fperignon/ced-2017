c	Calcul de C(i,j) = A(i,k) * B(k,j)
c
	implicit real*8 (a-h,o-z)

c	parameter (nmax=1024)
	parameter (nmax=1024)
	dimension a(nmax,nmax),b(nmax,nmax),c(nmax,nmax)
	parameter (nns=1)
        dimension ns(nns)

	real*4 etime, tarray(2)
	external etime
	real*8 time1, time2

        data ns/1024/
        logical llplain
        data llplain/.true./


        lda=nmax
        ldb=nmax
        ldc=nmax


        do iis=1,nns
        n=ns(iis)
        if (n.gt.nmax) stop

        nnn=(ns(nns)/ns(iis))**2
        ni=n
        nj=n
        nk=n
        xnop=2.0*(dfloat(n)**3)*nnn
        xop=xnop/1.0D+6

	do j=1,n
	do i=1,n
	   a(i,j)=(i+j)/(i+j+1.d0)
	   b(i,j)=i+j
	enddo
	enddo

        write(6,*)
	write(6,*) 'Matrix dimension ',nmax
	write(6,*) 'Problem dimension',n
	write(6,*) 'Number of passes ',nnn
	write(6,'(1x,a,1pe12.3)')
     $       'Number of floating operations',xnop
        write(6,*)
        
        if (llplain) then
        time1=etime(tarray)
	do l=1,nnn
           call plainMXM(A,LDA,B,LDB,C,LDC,NI,NK,NJ)
	enddo
        time2=etime(tarray)
        ttot=time2-time1
        write(6,10) 'plainMXM :', ttot, xop/ttot, c(n,n)
        endif

        time1=etime(tarray)
	do l=1,nnn
           call aixMXM(A,LDA,B,LDB,C,LDC,NI,NK,NJ)
	enddo
        time2=etime(tarray)
        ttot=time2-time1
        write(6,10) 'aixMXM :', ttot, xop/ttot, c(n,n)

        time1=etime(tarray)
	do l=1,nnn
          call blasMXM(A,LDA,B,LDB,C,LDC,NI,NK,NJ)
	enddo
        time2=etime(tarray)
        ttot=time2-time1
        write(6,10) 'blasMXM :', ttot, xop/ttot, c(n,n)

        enddo
 10     format(1x,a10,f12.3,' Secs',f12.3,' Mflops', 1pe14.6)
	end

      SUBROUTINE blasMXM(A,LDA,B,LDB,C,LDC,NI,NK,NJ)
      IMPLICIT REAL*8 (A-H,O-Z)
      DIMENSION A(LDA,1),B(LDB,1),C(LDC,1)
      DATA ZERO /0.0D+00/, one/1.0d0/
C
C     Apple a la routine blas pour le calcul de C = A * B
C
      DO 20 MJ=1,NJ
      DO 30 MI=1,NI
      C(MI,MJ)=ZERO
   30 CONTINUE
   20 CONTINUE

      call dgemm('n','n',ni,nj,nk,one,A,LDA,B,LDB,one,C,LDC)

      RETURN
      END

      SUBROUTINE aixMXM(A,LDA,B,LDB,C,LDC,NI,NK,NJ)
      IMPLICIT REAL*8 (A-H,O-Z)
      DIMENSION A(LDA,*),B(LDB,*),C(LDC,*)
      DATA ZERO /0.0D+00/
C     
C     C = A * B
C     Optimisation a la main, par blocs 4*4
C     
      nj4=(nj/4)*4
      nk4=(nk/4)*4
      
      do j=1,nj
         do i=1,ni
            c(i,j)=zero
         enddo
      enddo

      do j=1,nj4,4
         do k=1,nk4,4
            
            b00=b(k  ,j)
            b10=b(k+1,j)
            b20=b(k+2,j)
            b30=b(k+3,j)
            
            b01=b(k  ,j+1)
            b11=b(k+1,j+1)
            b21=b(k+2,j+1)
            b31=b(k+3,j+1)
            
            b02=b(k  ,j+2)
            b12=b(k+1,j+2)
            b22=b(k+2,j+2)
            b32=b(k+3,j+2)
            
            b03=b(k  ,j+3)
            b13=b(k+1,j+3)
            b23=b(k+2,j+3)
            b33=b(k+3,j+3)
            
            do i=1,ni
               c0=c(i,j  )
               c1=c(i,j+1)
               c2=c(i,j+2)
               c3=c(i,j+3)
               
               c0=c0+a(i,k  )*b00
               c1=c1+a(i,k  )*b01
               c2=c2+a(i,k  )*b02
               c3=c3+a(i,k  )*b03
               
               c0=c0+a(i,k+1)*b10
               c1=c1+a(i,k+1)*b11
               c2=c2+a(i,k+1)*b12
               c3=c3+a(i,k+1)*b13
               
               c0=c0+a(i,k+2)*b20
               c1=c1+a(i,k+2)*b21
               c2=c2+a(i,k+2)*b22
               c3=c3+a(i,k+2)*b23
               
               c0=c0+a(i,k+3)*b30
               c1=c1+a(i,k+3)*b31
               c2=c2+a(i,k+3)*b32
               c3=c3+a(i,k+3)*b33
               
               c(i,j  )=c0
               c(i,j+1)=c1
               c(i,j+2)=c2
               c(i,j+3)=c3
            enddo
         enddo
            
         do k=nk4+1,nk
            do i=1,ni
               c(i,j  )=c(i,j  )+a(i,k)*b(k,j  )
               c(i,j+1)=c(i,j+1)+a(i,k)*b(k,j+1)
               c(i,j+2)=c(i,j+2)+a(i,k)*b(k,j+2)
               c(i,j+3)=c(i,j+3)+a(i,k)*b(k,j+3)
            enddo
         enddo
      enddo
      
      do j=nj4+1,nj

         do k=1,nk
            do i=1,ni
               c(i,j)=c(i,j)+a(i,k)*b(k,j)
            enddo
         enddo

      enddo

      end

      SUBROUTINE plainMXM(A,LDA,B,LDB,C,LDC,NI,NK,NJ)
      IMPLICIT REAL*8 (A-H,O-Z)
      DIMENSION A(LDA,1),B(LDB,1),C(LDC,1)
      DATA ZERO /0.0D+00/
C     
C     C = A * B
C     Multiplication par une methode naive

      DO MJ=1,NJ
	 DO MI=1,NI
	    C(MI,MJ)=ZERO
	    DO MK=1,NK
	       C(MI,MJ)=C(MI,MJ)+A(MI,MK)*B(MK,MJ)
	    ENDDO
	 ENDDO
	ENDDO
	RETURN
	END
