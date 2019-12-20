su = load("/home/mikhail/matrix.txt");
n = size(su, 1);

X=zeros(1, n);
F=zeros(1, n);
A=zeros(n);

e = 0.0001;

for i=1:n
    for j=1:n
        A(i, j)=su(i, j);
    end
    F(i)=su(i, n+1);
end

s1 = sprintf("Jacobi(eps=%f):", e);
disp(s1);
resy = jacobi(A, F, n, e);

s2 = sprintf("Gauss-Zeidel(eps=%f):", e);
disp(s2);
resz = gz(A, F, n, e);
