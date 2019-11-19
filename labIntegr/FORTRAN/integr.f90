program main
  real a, b, e, e1
  a=0.6
  b=1.724
  e=0.0001
  e1=0.00001

  call trapeze(a, b, e)
  call rectangle(a, b, e)
  call simpson(a, b, e)
  print *
  call trapeze(a, b, e1)
  call rectangle(a, b, e1)
  call simpson(a, b, e1)
end program main

real function func(x)
  real x
  func=(x+x**3)**0.5
  return
end function func

subroutine trapeze(a, b, e)
  real a, b, c, res, h, buff, func
  integer n, trg
  n=1
  res=0
  buff=0
  trg=1
  do while (trg==1)
    h=(b-a)/n
    do i=1,n-1
       res=res+func(a+h*i)
    enddo
    res=(res*2+func(a)+func(b))*h/2
    if (abs(buff-res)<=(e*3)) then
      write(*, "(A15,f10.8,A6,i5,A6,f7.5 )") 'Trapeze: res = ', res, ', n = ', n, ', e = ', e
      trg=0;
    endif
    buff=res
    res=0
    n=n+1
  enddo
end subroutine trapeze

subroutine rectangle(a, b, e)
  real a, b, c, res, h, buff, func
  integer n, trg
  n=1
  res=0
  buff=0
  trg=1
  do while (trg==1)
    h=(b-a)/n
    do i=0,n-1
      res=res+func(a+h*i)
    enddo  
    res=res*h;
    if (abs(buff-res)<=(e*3)) then
      write(*, "(A23,f10.8,A6,i5,A6,f7.5 )") 'Rectangle(left): res = ', res, ', n = ', n, ', e = ', e
      n=1
      trg=0
    else 
      n=n+1
    endif
    buff=res
    res=0
  enddo
  trg=1
  do while (trg==1)
    h=(b-a)/n
      do i=1,n
        res=res+func(a+h*i)
      enddo
      res=res*h
      if (abs(buff-res)<=(e*3)) then
        write(*, "(A24,f10.8,A6,i5,A6,f7.5 )") 'Rectangle(right): res = ', res, ', n = ', n, ', e = ', e
        n=1
        trg=0
      else 
        n=n+1
      endif
      buff=res
      res=0
  enddo
  trg=1
  do while (trg==1)
    h=(b-a)/n
    do i=1,n-1
      res=res+func(a+h*i)
    enddo  
    res=(res+(func(a)+func(b))/2)*h
    if (abs(buff-res)<=(e*3)) then
      write(*, "(A25,f10.8,A6,i5,A6,f7.5 )") 'Rectangle(middle): res = ', res, ', n = ', n, ', e = ', e
      trg=0
    else 
      n=n+1
    endif
      buff=res
      res=0
  enddo
end subroutine rectangle

subroutine simpson(a, b, e)
  real a, b, c, res, h, buff, func, res1
  integer n, trg
  n=2
  res=0
  buff=0
  res1=0
  trg=1
  do while (trg==1)
    h=(b-a)/n/2
    do i=1,n
      res=res+func(a+h*(2*i-1))
    enddo
    res=res*4
    do i=1,n-1
      res1=res1+func(a+h*2*i)
    enddo
    res1=res1*2
    res=res+res1
    res=(res+func(a)+func(b))*h/3
    if (abs(buff-res)<=(e*15)) then
      write(*, "(A15,f10.8,A6,i5,A6,f7.5 )") 'Simpson: res = ', res, ', n = ', n, ', e = ', e
      trg=0
    endif
    buff=res
    res=0
    res1=0
    n=n+2
  enddo
end subroutine simpson
