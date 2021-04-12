                !!!!  This is spin up&down charge density !!!!


        real,allocatable :: t(:), m(:), numb(:)
        integer,allocatable :: natom(:)
        integer totalatom, nx, ny, nz, tot, k, satom
        character :: atmp

        open(15,file='CHGCAR')
!       open(16,file='POSCAR')
        open(17,file='chg.dat')
        open(18,file='1.dat')


        write(6,*) "please, write number of kind of atoms"
        read(5,*) satom

        allocate(natom(satom))

        read(15,*)
        read(15,*)
        read(15,*)
        read(15,*)
        read(15,*)
        read(15,*)
        read(15,*) (natom(i),i=1,satom)
        read(15,*)

!       write(6,*) (natom(i),i=1,satom)

        totalatom = 0

        DO i=1,satom
                totalatom= natom(i)+totalatom 
        ENDDO

!       write(6,*) totalatom

        DO i=1,totalatom
                read(15,*)
        ENDDO

        read(15,*)
        read(15,*) nx, ny, nz

        write(6,*) nx, ny, nz

        tot= nx*ny*nz

!       write(6,*) tot

!       write(6,*) "ok1"
        allocate(t(tot))
!       write(6,*) "ok2"
        read(15,*) (t(i),i=1,tot)
        

!       write(6,*) "ok3"

        DO i=1,tot
        write(18,*) t(i)
        ENDDO

        DO i=1,totalatom
!               write(6,*)" ok4"
                read(15,*) atmp, atmp, atmp, k
!               write(6,*)" ok5"
                allocate(numb(k))                
                read(15,*) (numb(j),j=1,k)
                deallocate(numb)
        ENDDO

        read(15,*)
        read(15,*)

        allocate(m(tot))

        read(15,*) (m(i),i=1,tot)

        DO i=1,tot
        write(17,*) (t(i) + m(i))/2
        ENDDO

        DO i=1,tot
        write(17,*) (t(i) - m(i))/2
        ENDDO

        write(6,*) "finish!!"


        CLOSE(15)
!       CLOSE(16)
        CLOSE(17)
        close(18)
        stop

        END
