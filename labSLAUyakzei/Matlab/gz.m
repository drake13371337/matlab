function [x] = gz(a, f, n, e)
    buff=zeros(1, n);
    x=zeros(1, n);
    counter = 0;
    while 1
        for i=1:n
            buff(i)=x(i);
        end
        for i=1:n
            sum = 0;
            for j=1:i-1
                sum=sum+a(i, j)*x(j);
            end
            for j=i+1:n
                sum=sum+a(i, j)*buff(j);
            end
            x(i)=(f(i)-sum)/a(i, i);
        end
        nr = abs(x(1)-buff(1));
        for i=1:n
            if abs(x(i)-buff(i))>nr
                nr=abs(x(i)-buff(i));
            end
            buff(i)=x(i);
        end
        counter=counter+1;
        if nr < e
            break;
        end
    end
    for i=1:n
        s6=sprintf("x%d = %f", i, x(i));
        disp(s6);
    end
    s7=sprintf("(n=%d)", counter);
    disp(s7);
end

