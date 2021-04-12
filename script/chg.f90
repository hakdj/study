
        !!!! This is charge difference !!!!


        real,allocatable :: t(:),a(:), b(:), diff(:), numb(:)
        integer,allocatable :: natom(:)
        integer satom, totalatom, tot, nx, ny, nz, totalatomA, first
        integer second, totalatomB, totA, totB, nxa, nya, nza, ntot
        integer nxb, nyb, nzb, k, spin, yes, no
        character(20) :: atmp, btmp, ctmp, dtmp, title, code
        real scf, aX, aY, aZ, bX, bY, bZ, cX, cY, cZ, Xx, Yy, Zz
        character(3),allocatable :: nnatom(:)

        open(15,file='AB')
        open(16,file='A')
        open(17,file='B')
!       open(16,file='POSCAR')
        open(18,file='CHGCAR_diff.vasp')
!       open(18,file='total.dat')

        write(6,*) "please, write number of kind of atoms"
        read(5,*) satom
        write(6,*) "please, write number of 1st charge density of atoms"
        read(5,*) first
        write(6,*) "please, write number of 2st charge density of atoms"
        read(5,*) second

        write(6,*) "This system is a spin polarization calculation?"
        write(6,*) " YES : 1  ,  NO : 2 "
        read(5,*) spin

        allocate(natom(satom),nnatom(satom))

        yes = 1
        no = 2

        read(15,*)  title
        write(18,*) title
        read(15,*)  scf
        write(18,*) scf
        read(15,*)  aX, aY, aZ
        write(18,*) aX, aY, aZ
        read(15,*)  bX, bY, bZ
        write(18,*) bX, bY, bZ
        read(15,*)  cX, cY, cZ
        write(18,*) cX, cY, cZ
        read(15,*)  (nnatom(i),i=1,satom)
        write(18,*) (nnatom(i),i=1,satom)

        read(15,*) (natom(i),i=1,satom)
        write(18,*) (natom(i),i=1,satom)

        read(15,*) atmp
        write(18,*) atmp

               
 
        totalatom = 0

        DO i=1,satom
                totalatom= natom(i)+totalatom
        ENDDO


        DO i=1,totalatom
                read(15,*) Xx, Yy, Zz
                write(18,*) Xx, Yy, Zz
        ENDDO

        write(18,*)
        read(15,*) nx, ny, nz
        write(18,*) nx, ny, nz

        tot= nx*ny*nz

        write(6,*)  (nnatom(i),i=1,satom)
        write(6,*)  (natom(i),i=1,satom)

!       write(6,*)  totalatom
        write(6,*)  "FFT-grid (NG(X,Y,Z)F)"
        write(6,*)  nx, ny, nz
        write(6,*)  tot

        allocate(t(tot))
  
!       write(6,*)"ok"
      
        read(15,*) (t(i),i=1,tot)

!       write(6,*) "ok2"
 
        totalatomA = 0
        DO i=1,first
        totalatomA = natom(i) +totalatomA
        ENDDO

!       write(6,*) totalatomA

        DO i=1,8
                read(16,*)
        ENDDO

        DO i=1,totalatomA
                read(16,*)
        ENDDO

        read(16,*) nxa, nya, nza 

        totA= nxa*nya*nza

        write(6,*) totA

        allocate(a(totA))
        
        read(16,*) (a(i),i=1,totA)


        ntot= first +second

        totalatomB = 0
        DO i=first+1,ntot
        totalatomB = natom(i) +totalatomB
        ENDDO

!       write(6,*) totalatomB

        DO i=1,8
                read(17,*)
        ENDDO

        DO i=1,totalatomB
                read(17,*)
        ENDDO

        read(17,*) nxb, nyb, nzb 

        totB= nxb * nyb * nzb

        write(6,*) totB

        allocate(b(totB))
        

        read(17,*) (b(i),i=1,totB)


        allocate(diff(tot))


        DO i=1,tot
                diff(i) = t(i) - a(i) - b(i)
        ENDDO


        write(18,*) (diff(i),i=1,tot)

        if(spin .EQ. yes) then

        deallocate (t) 
        deallocate (a) 
        deallocate (b) 
        deallocate (diff) 

        DO i=1,totalatom
!               write(6,*) "ok4"
                read(15,*) btmp, ctmp, dtmp, k
                write(18,*) btmp, ctmp, dtmp, k
!               write(6,*) "ok5"
                allocate(numb(k))
                read(15,*) (numb(j),j=1,k)
                write(18,*) (numb(j),j=1,k)
                deallocate(numb)
!               write(6,*) "ok6"
        ENDDO


        DO i=1,totalatomA
!               write(6,*) "ok4"
                read(16,*) btmp, ctmp, dtmp, k
!               write(6,*) "ok5"
                allocate(numb(k))
                read(16,*) (numb(j),j=1,k)
                deallocate(numb)
!               write(6,*) "ok6"
        ENDDO

        DO i=1,totalatomB
!               write(6,*) "ok4"
                read(17,*) btmp, ctmp, dtmp, k
!               write(6,*) "ok5"
                allocate(numb(k))
                read(17,*) (numb(j),j=1,k)
                deallocate(numb)
!               write(6,*) "ok6"
        ENDDO

        allocate(t(tot),a(totA),b(totB),diff(tot))

        read(15,*) (t(i),i=1,tot)
        read(16,*) (a(i),i=1,totA)
        read(17,*) (b(i),i=1,totB)

        DO i=1,tot
                diff(i) = t(i) - a(i) - b(i)
        ENDDO


        write(18,*) (diff(i),i=1,tot)

        
        close(15) 
        close(16)
        close(17)
        close(18)


        STOP
        else if (spin .EQ. no) then 



        close(15) 
        close(16)
        close(17)
        close(18)

        stop   
       
        end if
 
        END






































