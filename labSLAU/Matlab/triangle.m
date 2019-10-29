function [res] = triangle(matrix, n, step)
    trg=0
    res=matrix
    if(n == 0)
        trg=1
    end
    if(trg==0)
        for i=1:n-1
            imax = col_max(res, i, n)
            if(i~=imax)
                for j=1:n+step
                    buff=res(i, j)
                    res(i, j)=res(imax, j)
                    res(imax, j)=buff
                end
            end
            for j=i+1:n
                mul = 0
                if (res(i, i)==0)
                    mul=0
                end
                if (res(i, i)~=0)
                    mul=-res(j, i)/res(i, i)
                end
                for k=i:n+step
                    res(j, k)=res(j, k)+res(i, k)*mul
                    if (abs(res(j, k))<0.0001)
                        res(j, k) = 0
                    end
                end
            end
        end
    end
end
