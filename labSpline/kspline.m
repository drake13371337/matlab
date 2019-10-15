function [d, c, b, a]  = kspline(x, y)
    n = length(x);
    h = diff(x);

    k1 = 1./h(2:n-2);
    k2 = 2* (1./h(1:n-2) + 1./h(2:n-1));
    k3 = 1./h(2:n-2);

    D3 = [[k1; 0] k2 [0; k3]];
    A = spdiags(D3, [-1 0 1], n-2, n-2);

    df = diff(y)./h;
    k4 = 3*(df(2:n-1)./h(2:n-1) + df(1:n-2)./h(1:n-2));
    b = A\k4;
    b = [0; b; 0];

    a = y(1:n-1);
    c = (3*df - b(2:n) - 2*b(1:n-1))./h;
    d = (b(1:n-1) + b(2:n) - 2*df)./h.^2;
    b(end) = [];
end