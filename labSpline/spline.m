function [y] = spline(x1, y1, x)
    n = length(x1);
    x1 = x1(:);
    y1 = y1(:);

    [d, c, b, a]  = kspline(x1, y1);
    y = zeros(size(x));

    for k=1:n-1
        ind = find((x >= x1(k)) & (x<= x1(k+1)));
        y(ind) = a(k) + b(k)*(x(ind)-x1(k))+c(k)*(x(ind)-x1(k)).^2 + d(k)*(x(ind)-x1(k)).^3;
    end
end