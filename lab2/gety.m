function [y] = gety(n, x, xx, yy)
    y = zeros(1, n);
    for r=1:n
        for k=1:size(xx)
            if x(r)==xx(k)
                y(r)=yy(k);
            end
        end
    end
    for r=1:n
        if y(r)==0
            t=mod(x(r), 2);
            x1=x(r)-t;
            x2=x1+2;
            y1=0;
            y2=0;
            for k=1:size(xx)
                if x1==xx(k)
                    y1=yy(k);
                end
            end
            for k=1:size(xx)
                if x2==xx(k)
                    y2=yy(k);
                end
            end
            y(r)=(y2-y1)*(x(r)-x1)/(x2-x1)+y1;
        end
    end
end
