
        real,allocatable :: energy(:,:,:), totalenergy(:), ev(:)
        integer,allocatable :: natom(:)
        integer  nx, ny, nz, satom, totalatom, tot 
        real x, y, z, zdat, fermi, atmp

        open(15,file='LOCPOT')
        open(16,file='LOC.dat')
        open(17,file='POSCAR')
        open(18,file='DOSCAR')        

        write(6,*) "please, write number of kind of atoms"
        read(5,*) satom        
        
        allocate(natom(satom))

        read(15,*)
        read(15,*)
        read(15,*)
!       write(6,*) "test1" 
        read(15,*)
        read(15,*)
        read(15,*)
        read(15,*) (natom(i),i=1,satom) 

        write(6,*) (natom(i),i=1,satom) 

!       write(6,*) "test2" 

        read(15,*)
                
        totalatom=0

        Do i=1,satom
                totalatom= natom(i)+totalatom
!               write(6,*) totalatom ,i
        ENDDO
        
        
        read(18,*)
        read(18,*)
        read(18,*)
        read(18,*)
        read(18,*)
        read(18,*) atmp, atmp, atmp, fermi 

        DO i=1, totalatom

!               write(6,*) "test ",i


                read(15,*)

        ENDDO

!       close(15)
!       stop

        read(15,*)

        read(15,*) nx, ny, nz

        tot = nx*ny*nz

        allocate(energy(nx,ny,nz),ev(tot))

        read(15,*) (ev(i),i=1,tot)

        DO k=1,nz
                DO j=1,ny
                        DO i=1,nx
                                l=(i-1) + nx*(j-1) + nx*ny*(k-1) + 1
                                energy(i,j,k) = ev(l)
                        ENDDO
                ENDDO
        ENDDO
        
        read(17,*)
        read(17,*)
        read(17,*)
        read(17,*)
        read(17,*) x, y, z

        zdat= nz/z

        
        allocate(totalenergy(nz))

        DO k=1,nz
                DO j=1,ny
                        Do i=1,nx
                                totalenergy(k) =  energy(i,j,k)+totalenergy(k)
                        ENDDO
                ENDDO
                write(16,*) k/zdat, totalenergy(k)/(nx*ny) -1 * fermi 
        ENDDO

        

!       allocate(energy(nx*ny*nz/5,5,nz))!,btmp(nx*ny*nz/5,2),ctmp(nx*ny*nz/5,2),dtmp(nx*ny*nz/5,2),etmp(nx*nz*ny/5,2))

!       Do k=1,nz
!               DO i=1, nx*ny/5

!                      read(15,*)  energy(i,1,k), energy(i,2,k), energy(i,3,k), energy(i,4,k), energy(i,5,k)

!               write(6,*) "test", i

!               ENDDO
!       ENDDO


!       close(15)
!       stop
!       allocate(totalenergy(nx*ny/5,nz))
!       
!       totalenergy(nx*ny/5,nz)=0

!       DO k=1, nz

!               DO i=1, nx*ny/5

!                      totalenergy() =  energy(i,1,k)+ energy(i,2,k)+ energy(i,3,k)+ energy(i,4,k)+ energy(i,5,k) + totalenergy(k)

!               ENDDO

!               write(16,*) k, totalenergy(k)

!       ENDDO

        CLOSE(15)
        CLOSE(16)
        CLOSE(17)

        stop

        end

