program main
  integer n, tmp_rank, rank_matr
  real, allocatable :: su(:,:)
  real, allocatable :: tmp(:,:)
  n=0
  open(1, file='matrix.txt')
  do
     read(1,*, iostat=io)
     if(io/=0) exit
     n=n+1
  enddo
  close(1)
  allocate(su(n, n+1))
  allocate(tmp(n, n))
  
  open(2, file='matrix.txt')
  do i=1,n
     read(2, *)(su(i,j),j=1,n+1)
  enddo
  close(2)

  do i=1,n
     do j=1,n
        tmp(i,j)=su(i,j)
     enddo
  enddo
  tmp_rank=rank_matr(tmp, n, 0)
  call triangle(su, n, 1)
  call triangle(tmp, n, 0)
  call gauss(su, tmp_rank, n)
  
  deallocate(su)
  deallocate(tmp)
end program main

subroutine print_matr(matr, n, step)
  integer n, step
  real , dimension(n, step+n) :: matr
  do i=1,n
     do j=1,n+step
        write(*, "(f10.4, 1x)") matr(i, j)
     enddo
     write(*,*)
  enddo
  return
end subroutine print_matr

integer function col_max(matrix, col, n)
  integer n, col, maxpos
  real max, element
  real , dimension(n, n) :: matrix
  max = abs(matrix(col, col))
  maxPos = col
  do i=col+1,n
     element = abs(matrix(i, col))
     if (element>max) then
         max = element
         maxPos = i
     endif
  enddo
  col_max=maxpos
  return
end function col_max

subroutine triangle(matrix, n, step)
  real buff, mul
  integer n, step, imax
  real , dimension(n, n+step) :: matrix
  integer col_max
  
  if (n == 0) then
     stop
  endif
  do i=1,n-1
     imax = col_max(matrix, i, n)
     if (i .ne. imax) then
         do j=1,n+step
             buff=matrix(i, j)
             matrix(i, j)=matrix(imax, j)
             matrix(imax, j)=buff
         enddo
     endif
     do j=i+1,n
        if(matrix(i, i)==0) then
           mul=0;
        endif
        if(matrix(i, i).ne.0) then
           mul = -matrix(j, i)/matrix(i, i)
        endif
        do k=i,n+step
           matrix(j, k)=matrix(j, k)+matrix(i, k)*mul;
           if(abs(matrix(j, k))<0.0001) then
              matrix(j, k)=0;
           endif
        enddo
     enddo
  enddo
  return
end subroutine triangle

integer function rank_matr(matrix, n, step)
  integer n, step, rank1, chk
  real , dimension(n, n+step) :: matrix
  rank1=n
  do i=0,n-1
     chk=0;
     do j=1,n+step
         if(matrix(n-i, j).ne.0) then
            chk=chk+1
         endif
     enddo
     if(chk==0) then
        rank1=rank1-1
     endif
  enddo
  rank_matr=rank1
  return
end function rank_matr

subroutine gauss(matr, rank, n)
  integer ranks, rank_matr, n, rank
  real , dimension(n, n+1) :: matr
  real, allocatable :: x(:)
  allocate(x(n))
  ranks=rank_matr(matr, n, 1)
  if((ranks==rank).and.(ranks<n)) then
     print *, "Endless solutions"
     deallocate(x)
     return
  endif
  if(rank==ranks)then
     do i=0,n-1
        x(n-i)=matr(n-i, n+1)
        do j=1,n
           if((n-i).ne.j) then
              x(n-i)=x(n-i)-(matr(n-i, j)*x(j))
           endif
        enddo
        x(n-i)=x(n-i)/matr(n-i, n-i)
        if(matr(n-i, n-i).eq.0) then
           print *, "Endless solution"
        endif
        if(matr(n-i, n-i).ne.0) then
           print 15, n-i-1, x(n-i)
           15 FORMAT(1x, "X", i1, " = ", 1x, f10.4)
        endif  
     enddo
     deallocate(x)
     return
  endif
  print *, "No solutions"
  deallocate(x)
  return
end subroutine gauss
  
