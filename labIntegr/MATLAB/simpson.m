function simpson(a, b, e)
    n=0;
    res=0;
    buff=0;
    res1=0;

    while true
        h=(b-a)/n/2;

        for i=1:n
            res=res+func(a+h*(2*i-1));
        end
        res=res*4;
        for i=1:n-1
            res1=res1+func(a+h*2*i);
        end
        res1=res1*2;
        res=res+res1;

        res=(res+func(a)+func(b))*h/3;

        if(abs(buff-res)<=(e*15))
            str=fprintf("Simpson: res = %f, n = %d, e = %f", res, n, e);
            disp(" ");
            break;
        end
        buff=res;
        res=0;
        res1=0;
        n=n+2;
    end
end