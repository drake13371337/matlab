function [x1, res] = gauss(matr, rankm, n)
    trg = 0
    x1 = zeros(0, 0)
    x = zeros(1, n)
    res="none"
    for i=1:n
        x(i)=0
    end
    
    ranks=rank(matr)
    
    if(ranks == rankm && ranks < n)
        res="Endless solutions"
        trg=1
    end
    if(rankm == ranks && trg==0)
        for i=n:-1:1
            x(i) = matr(i, n+1);
            for j=1:n
                if(i~=j)
                    x(i)=x(i)-(matr(i, j)*x(j))
                end
            end
            x(i)=x(i)/matr(i, i);
            if(matr(i, i) == 0)
                res="Endless solutions"
            end
            if(matr(i, i) ~= 0)
                x1=[x1 x(i)]
            end
        end
        trg=1
    end
    if(trg==0) 
        res="No solutions"
    end
end

