function rectangle(a, b, e)
    n=2;
    trg = 1;
    res=0;
    buff=0;
    while trg
        h=(b-a)/n;

        for i=0:n-1
            res=res+func(a+h*i);
        end

        res=res*h;

        if(abs(buff-res)<=(e*3))
            fprintf("Rectangle(left): res = %f, n = %d, e = %f", res, n, e);
            disp(" ");
            n=1;
            trg=0;
        else
            n=n+1;
        end
        buff=res;
        res=0;
    end
    trg=1;
    while trg
        h=(b-a)/n;

        for i=1:n
            res=res+func(a+h*i);
        end

        res=res*h;

        if(abs(buff-res)<=(e*3))
            fprintf("Rectangle(right): res = %f, n = %d, e = %f", res, n, e);
            disp(" ");
            trg=0;
            n=1;
        else
            n=n+1;
        end
        buff=res;
        res=0;    
    end
    trg=1;
    while trg
        h=(b-a)/n;

        for i=1:n-1
            res=res+func(a+h*i);
        end

        res=res+(func(a)+func(b))/2;
        res=res*h;
        
        if(abs(buff-res)<=(e*3))
            fprintf("Rectangle(middle): res = %f, n = %d, e = %f", res, n, e);
            disp(" ");
            trg=0;
        else
            n=n+1;
        end
        buff=res;
        res=0;
    end
end
