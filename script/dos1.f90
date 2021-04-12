        integer,allocatable :: natom(:)
        real,allocatable :: b(:,:),ev(:),dos(:,:,:),s(:),p(:),d(:),t(:),btmp(:,:)
        integer a, q, w, e, r, NEDOS, satom, totalatom, first, second
        real atmp, fermi

        open(15,file='DOSCAR')
        open(16,file='POSCAR')
        open(20,file='Total-DOS.dat')
!       open(21,file='PDOS-1.dat')
        open(22,file='PDOS-1-total.dat')
!       open(23,file='PDOS-2.dat')
        open(24,file='PDOS-2-total.dat')
        open(25,file='Total-DOS2.dat')
        read(15,*)a

        read(15,*)
        read(15,*)
        read(15,*)
        read(15,*)
        read(15,*)atmp,atmp,NEDOS,fermi

        allocate( b(NEDOS,3),ev(NEDOS),dos(a,NEDOS,3),s(NEDOS),p(NEDOS),d(NEDOS), t(NEDOS))

        DO i=1,NEDOS
        read(15,*)b(i,1),b(i,2),b(i,3)
        ENDDO

        DO j=1,NEDOS 
        write(20,*)b(j,1),b(j,2)
        ENDDO

        
        close(20)

        


        DO k=1,a
                read(15,*)
                DO l=1,NEDOS
                        read(15,*)ev(l),dos(k,l,1),dos(k,l,2),dos(k,l,3)
                ENDDO
        ENDDO

        write(6,*) "please, write number of kind of atoms"
        read(5,*) satom
        
        allocate(natom(satom))

        read(16,*)
        read(16,*)
        read(16,*)
        read(16,*)
        read(16,*)
        read(16,*)
        read(16,*) (natom(i),i=1,satom)

        write(6,*) (natom(i),i=1,satom)
        
        write(6,*) "please, write number of kind of first PDOS"
        read(5,*) q
        write(6,*) "please, write number of kidn of second PODS"
        read(5,*) w

                e= q+w



        if(e .NE. satom) then
        write(6,*) "you write wrong number of kind of atom."
        STOP
        else if (e .EQ.  satom)then
        write(6,*) "right!"
        end if

                totalatom=0
        DO i=1, satom
                totalatom= natom(i)+totalatom
        ENDDO

                first=0
        Do i=1,q
                first= natom(i)+first
        ENDDO

                second=0
        DO i=q+1,e
                second= natom(i)+second
        ENDDO
        write(6,*) first, second









        DO l=1,NEDOS
                s(l)=0
                p(l)=0
                d(l)=0
                t(l)=0
        DO m=1, first
                s(l) = dos(m,l,1)+s(l)
                p(l) = dos(m,l,2)+p(l)
                d(l) = dos(m,l,3)+d(l)
                t(l) = s(l) + p(l) + d(l)         
        ENDDO

!       write(21,*)ev(l), s(l), p(l), d(l)
                ev(l)= ev(l) -1 * fermi ! write fermi-E
        write(22,*)ev(l), t(l)
        ENDDO
        

        DO l=1,NEDOS
                s(l)=0
                p(l)=0
                d(l)=0
                t(l)=0
        DO m= first+1, first + second
                s(l) = dos(m,l,1)+s(l)
                p(l) = dos(m,l,2)+p(l)
                d(l) = dos(m,l,3)+d(l)
                t(l) = s(l) + p(l) + d(l)         
        ENDDO

!       write(23,*)ev(l), s(l), p(l), d(l)
!               ev(l)= ev(l) +2.3461
        write(24,*)ev(l), t(l)
        ENDDO
       


        DO l=1,NEDOS
                s(l)=0
                p(l)=0
                d(l)=0
                t(l)=0
        DO m=1,totalatom
                s(l) = dos(m,l,1)+s(l)
                p(l) = dos(m,l,2)+p(l)
                d(l) = dos(m,l,3)+d(l)
                t(l) = s(l) + p(l) + d(l)         
        ENDDO
!               ev(l)= ev(l) +2.3461
        write(25,*)ev(l), t(l) 
        ENDDO



        close(15)
        close(16)
!       close(21)
        close(22)
!       close(23)
        close(24)
        close(25)

        stop

                END
