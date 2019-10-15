function [yn] = newt(n, xx, x, y)
    y3 = y;
    for  k = 1 : n-1
        for i = 1: n - k
        y3(i) = (y3(i+1) - y3(i)) / (x(i+k) - x(i));
        end
    end
    yn = y3(1) * ones(size(xx));
    for k = 2 : n
        yn = y3(k) + (xx - x(k)) .* yn;
    end
end

