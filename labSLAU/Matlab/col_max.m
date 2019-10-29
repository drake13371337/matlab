function [maxpos] = col_max(matrix, a, n)
    maxc = abs(matrix(a, a))
    maxpos = a
    for i=a+1:n
        element=abs(matrix(i, a))
        if element>maxc
            maxc=element
            maxpos=i
        end
    end
end


