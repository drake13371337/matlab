function [yl] = lagr(n, xx, x, y)
    yl=0;
    for k=1:n
        p=1;
        for i=[1:k-1,k+1:n]
            p=p.*(xx-x(i))/(x(k)-x(i));
        end
        yl=yl+y(k).*p;
    end
end

