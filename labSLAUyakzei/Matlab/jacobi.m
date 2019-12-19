function [x] = jacobi(a, f, n, e)
    buff=zeros(1, n);
    x=zeros(1, n);
    counter = 0;
    
    while 1
        for i=1:n
            buff(i)=f(i);
            for j=1:n
                if i~=j
                    buff(i)=buff(i)-a(i, j)*x(j);
                end
            end
            buff(i)=buff(i)/a(i, i);
        end
        nr = abs(x(1)-buff(1));
        for i=1:n
            if abs(x(i)-buff(i))>nr
                nr=abs(x(i)-buff(i));
            end
            x(i)=buff(i);
        end
        counter=counter+1;
        if nr < e
            break;
        end
    end
    for i=1:n
        s9=sprintf("x%d = %f", i, x(i));
        disp(s9);
    end
    s8=sprintf("(n=%d)", counter);
    disp(s8);
end

