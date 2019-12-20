program main
  integer n
  real, allocatable :: su(:,:)
  real, allocatable :: A(:,:)
  real, allocatable :: F(:)
  real e
  n=0
  open(1, file='matrix.txt')
  do
     read(1,*, iostat=io)
     if(io/=0) exit
     n=n+1
  enddo
  close(1)
  allocate(su(n, n+1))
  allocate(A(n, n))
  allocate(F(n))

  open(2, file='matrix.txt')
  do i=1,n
     read(2, *)(su(i,j),j=1,n+1)
  enddo
  close(2)

  do i=1,n
     do j=1,n
        A(i,j)=su(i,j)
     enddo
     F(i)=su(i, n+1)
  enddo

  e=0.0001
  write(*,"(A11, f6.4, A1)") "Jacobi(eps=", e, ")"
  call jacobi(A, F, n, e)
  print *
  write(*,"(A17, f6.4, A1)") "Gauss-Zeidel(eps=", e, ")"
  call gz(A, F, n, e)

  deallocate(su)
  deallocate(A)
  deallocate(F)
end program main

subroutine jacobi(a, f, n, e)
  real , dimension(n, n) :: a
  real , dimension(n) :: f
  real , dimension(n) :: x
  real , dimension(n) :: buff
  real e, nr
  integer n, counter, tg, i, j
  counter = 0
  tg=1
  do i=1, n
    x(i)=0
  enddo

  do while (tg==1)
    do i=1, n
      buff(i)=f(i)
      do j=1, n
        if (i /= j) then
          buff(i)=buff(i)-a(i, j)*x(j)
        endif
      enddo
      buff(i)=buff(i)/a(i, i)
    enddo
    nr=abs(x(1)-buff(1))
    do i=1, n
      if(abs(x(i)-buff(i))>nr) then
        nr=abs(x(i)-buff(i))
      endif
      x(i)=buff(i)
    enddo
    counter=counter+1
    if(nr<e) then
      tg=0
    endif
  enddo
  do i=1, n
      write(*,"(A1, i1, A3, f12.8)") "x", i, " = ", x(i)
  enddo
  write(*,"(A3, i3, A1)") "(n=)", counter, ")"
end subroutine jacobi

subroutine gz(a, f, n, e)
  real , dimension(n, n) :: a
  real , dimension(n) :: f
  real , dimension(n) :: x
  real , dimension(n) :: buff
  real e, nr, sum
  integer n, counter, tg, i, j
  counter = 0
  tg=1

  do i=1, n
    x(i)=0
  enddo

  do while (tg==1)
    do i=1, n
      buff(i)=x(i)
    enddo
    do i=1, n
      sum = 0
      do j=1,i-1
        sum=sum+a(i, j)*x(j)
      enddo
      do j=i+1,n
        sum=sum+a(i, j)*buff(j)
      enddo
      x(i)=(f(i)-sum)/a(i, i)
    enddo
    nr=abs(x(1)-buff(1))
    do i=1, n
      if(abs(x(i)-buff(i))>nr) then
        nr=abs(x(i)-buff(i))
      endif
      buff(i)=x(i)
    enddo
    counter=counter+1
    if(nr<e) then
      tg=0
    endif
  enddo
  do i=1, n
      write(*,"(A1, i1, A3, f12.8)") "x", i, " = ", x(i)
  enddo
  write(*,"(A3, i3, A1)") "(n=)", counter, ")"
end subroutine gz
