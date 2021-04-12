
        !!!! This is charge difference !!!!


        real,allocatable :: tu(:), au(:), bu(:), diffu(:), numb(:)
        real,allocatable :: td(:), ad(:), bd(:), diffd(:)
        real,allocatable :: trasht(:), trasha(:), trashb(:)
        real,allocatable :: df(:),diff(:,:,:)
        integer,allocatable :: natom(:)
        integer satom, totalatom, tot, nx, ny, nz, totalatomA, first
        integer second, totalatomB, totA, totB, nxa, nya, nza, ntot
        integer nxb, nyb, nzb, k, spin, yes, no, plot, yess, noo
        character(20) :: atmp, btmp, ctmp, dtmp, title, code
        real scf, aX, aY, aZ, bX, bY, bZ, cX, cY, cZ, Xx, Yy, Zz
        character(3),allocatable :: nnatom(:)
        real x, y, z, zdat


        open(15,file='AB')
        open(16,file='A')
        open(17,file='B')
        open(21,file='POSCAR')

        write(6,*) "please, write number of kind of atoms"
        read(5,*) satom
        write(6,*) "please, write number of 1st charge density of atoms"
        read(5,*) first
        write(6,*) "please, write number of 2st charge density of atoms"
        read(5,*) second

        write(6,*) "This system is a spin polarization calculation?"
        write(6,*) " YES : 1  ,  NO : 2 "
        read(5,*) spin
        write(6,*) "Will you calculation of chargedifference plot?"
        write(6,*) " YES : 1  ,  NO : 2 "
        read(5,*) plot

        allocate(natom(satom),nnatom(satom))

        yess = 1
        noo = 2
        yes = 1
        no = 2

        if(spin .EQ. yes) then

        open(18,file='CHGCAR_diff-up.vasp')
        open(19,file='CHGCAR_diff-down.vasp')

        read(15,*)  title
        write(18,*) title
        write(19,*) title
        read(15,*)  scf
        write(18,*) scf
        write(19,*) scf
        read(15,*)  aX, aY, aZ
        write(18,*) aX, aY, aZ
        write(19,*) aX, aY, aZ
        read(15,*)  bX, bY, bZ
        write(18,*) bX, bY, bZ
        write(19,*) bX, bY, bZ
        read(15,*)  cX, cY, cZ
        write(18,*) cX, cY, cZ
        write(19,*) cX, cY, cZ
        read(15,*)  (nnatom(i),i=1,satom)
        write(18,*) (nnatom(i),i=1,satom)
        write(19,*) (nnatom(i),i=1,satom)

        read(15,*) (natom(i),i=1,satom)
        write(18,*) (natom(i),i=1,satom)
        write(19,*) (natom(i),i=1,satom)

        read(15,*) atmp
        write(18,*) atmp
        write(19,*) atmp

        totalatom = 0

        DO i=1,satom
                totalatom= natom(i)+totalatom
        ENDDO


        DO i=1,totalatom
                read(15,*) Xx, Yy, Zz
                write(18,*) Xx, Yy, Zz
                write(19,*) Xx, Yy, Zz
        ENDDO

        write(18,*)
        write(19,*)
        read(15,*) nx, ny, nz
        write(18,*) nx, ny, nz
        write(19,*) nx, ny, nz


        else if(spin .EQ. no) then 
               
        open(20,file='CHGCAR_diff.vasp')

        read(15,*)  title
        write(20,*) title
        read(15,*)  scf
        write(20,*) scf
        read(15,*)  aX, aY, aZ
        write(20,*) aX, aY, aZ
        read(15,*)  bX, bY, bZ
        write(20,*) bX, bY, bZ
        read(15,*)  cX, cY, cZ
        write(20,*) cX, cY, cZ
        read(15,*)  (nnatom(i),i=1,satom)
        write(20,*) (nnatom(i),i=1,satom)

        read(15,*) (natom(i),i=1,satom)
        write(20,*) (natom(i),i=1,satom)

        read(15,*) atmp
        write(20,*) atmp

        totalatom = 0

        DO i=1,satom
                totalatom= natom(i)+totalatom
        ENDDO


        DO i=1,totalatom
                read(15,*) Xx, Yy, Zz
                write(20,*) Xx, Yy, Zz
        ENDDO

        write(20,*)
        read(15,*) nx, ny, nz
        write(20,*) nx, ny, nz



        end if


        tot= nx*ny*nz

        write(6,*)  (nnatom(i),i=1,satom)
        write(6,*)  (natom(i),i=1,satom)

!       write(6,*)  totalatom
        write(6,*)  "FFT-grid (NG(X,Y,Z)F)"
        write(6,*)  nx, ny, nz
        write(6,*)  tot

        allocate(tu(tot))
  
!       write(6,*)"ok"
      
        read(15,*) (tu(i),i=1,tot)

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

        allocate(au(totA))
        
        read(16,*) (au(i),i=1,totA)


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

        allocate(bu(totB))
        

        read(17,*) (bu(i),i=1,totB)


        allocate(diffu(tot))


        DO i=1,tot
                diffu(i) = tu(i) - au(i) - bu(i)
        ENDDO


!       write(18,*) (diffu(i),i=1,tot)

        if(spin .EQ. yes) then


        DO i=1,totalatom
!               write(6,*) "ok4"
                read(15,*) btmp, ctmp, dtmp, k
!               write(18,*) btmp, ctmp, dtmp, k
!               write(19,*) btmp, ctmp, dtmp, k
!               write(6,*) "ok5"
                allocate(numb(k))
                read(15,*) (numb(j),j=1,k)
!               write(18,*) (numb(j),j=1,k)
!               write(19,*) (numb(j),j=1,k)
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

        allocate(td(tot),ad(totA),bd(totB),diffd(tot),)
        allocate(trasht(totalatom),trasha(totalatomA),trashb(totalatomB))

        read(15,*) (trasht(i),i=1,totalatom)
        read(15,*) atmp, atmp, atmp
        read(16,*) (trasha(i),i=1,totalatomA)
        read(16,*) atmp, atmp, atmp
        read(17,*) (trashb(i),i=1,totalatomB)
        read(17,*) atmp, atmp, atmp

 
        read(15,*) (td(i),i=1,tot)
        read(16,*) (ad(i),i=1,totA)
        read(17,*) (bd(i),i=1,totB)

        DO i=1,tot
                diffd(i) = td(i) - ad(i) - bd(i)
        ENDDO

        DO i=1,tot
             write(18,*) (diffu(i)+diffd(i)) / 2   
        ENDDO
        DO i=1,tot
             write(19,*) (diffu(i)-diffd(i)) / 2   
        ENDDO


                        !!!!!      diff plot    !!!!!!

        if (plot .EQ. yess) then

        open(22,file='diffplot-up.dat')
        open(23,file='diffplot-down.dat')


        read(21,*)       
        read(21,*)       
        read(21,*)       
        read(21,*)       
        read(21,*)   x, y, z    

        zdat= nz/z

        allocate(df(nz))

        
        allocate(diff(nx,ny,nz))

        DO k=1,nz
                DO j=1,ny
                        DO i=1,nx
                                l=(i-1) + nx*(j-1) + nx*ny*(k-1) + 1
                                diff(i,j,k) = diffu(l)
                        ENDDO
                ENDDO   
        ENDDO


        DO k=1,nz
                DO j=1,ny
                        DO i=1,nx
                                df(k)= diff(i,j,k) + df(k)
                        ENDDO
                ENDDO
                write(22,*) k/zdat, df(k)/(nx*ny)
        ENDDO



        DO k=1,nz
                DO j=1,ny
                        DO i=1,nx
                                l=(i-1) + nx*(j-1) + nx*ny*(k-1) + 1
                                diff(i,j,k) = diffd(l)
                        ENDDO
                ENDDO   
        ENDDO

        DO k=1,nz
                DO j=1,ny
                        DO i=1,nx
                                df(k)= diff(i,j,k) + df(k)
                        ENDDO
                ENDDO
                write(23,*) k/zdat,  df(k)/(nx*ny)
        ENDDO

        close(15)
        close(16)
        close(18)
        close(19)
        close(17)
        close(21)
        close(22)
        close(23)

        stop

        else if (plot .EQ. noo) then

        close(15)
        close(16)
        close(18)
        close(19)
        close(17)
        close(21)

        stop

        end if

        else if (spin .EQ. no) then 

        Do i=1,tot
        write(20,*) diffu(i)
        ENDDO

       
                        !!!!!      diff plot    !!!!!!

        if (plot .EQ. yess) then

        open(24,file='diffplot.dat')

        read(21,*)       
        read(21,*)       
        read(21,*)       
        read(21,*)       
        read(21,*)   x, y, z    

        zdat= nz/z

        allocate(df(nz))

        
        allocate(diff(nx,ny,nz))

        DO k=1,nz
                DO j=1,ny
                        DO i=1,nx
                                l=(i-1) + nx*(j-1) + nx*ny*(k-1) + 1
                                diff(i,j,k) = diffu(l)
                        ENDDO
                ENDDO   
        ENDDO


        DO k=1,nz
                DO j=1,ny
                        DO i=1,nx
                                df(k)= diff(i,j,k) + df(k)
                        ENDDO
                ENDDO
                write(24,*) k/zdat, df(k)/(nx*ny)
        ENDDO

        close(15)
        close(16)
        close(17)
        close(20)
        close(21)
        close(24)

        stop        

        else if (plot .EQ. noo) then

        close(15)
        close(16)
        close(17)
        close(20)
        close(21)


        stop

        end if

        end if
 
        END


