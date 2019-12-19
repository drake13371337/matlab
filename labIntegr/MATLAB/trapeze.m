function trapeze(a, b, e)
    n=1;
    res=0;
    buff=0;
    while 1
        h=(b-a)/n;
        for i=1:(n-1)
            res=res+func(a+h*i);
        end
        res=(res*2+func(a)+func(b))*h/2;

        if(abs(buff-res)<=(e*3))
            fprintf("Trapeze: res = %f, n = %d, e = %f", res, n, e);
            disp(" ");
            break
        end
        buff=res;
        res=0;
        n=n+1;
    end
end

