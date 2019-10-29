su = load("/home/mikhail/matrix.txt")
n = size(su, 1)
tmp=zeros(n)

for i=1:n
    for j=1:n
        tmp(i, j)=su(i, j)
    end
end

su = triangle(su, n, 1)
tmp = triangle(tmp, n, 0)
[x, res] = gaus(su, rank(tmp), n)
clc
if(res=="none")
    for i=1:size(x, 2)
        fprintf("x%i = %f\n", size(x, 2)-i, x(i))
    end
end
if(res~="none")
   disp(res) 
end