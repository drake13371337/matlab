import math


def gz(a, f, n, e):
    buff = []
    counter = 0
    x = []
    for i in range(n):
        x.append(0.0)
        buff.append(0.0)
    while 1:
        for i in range(n):
            buff[i] = x[i]
        for i in range(n):
            sum = 0
            for j in range(i):
                sum += (a[i][j]*x[j])
            for j in range(i+1, n):
                sum += (a[i][j]*buff[j])
            x[i] = (f[i]-sum)/a[i][i]
        nr = math.fabs(buff[0]-x[0])
        for k in range(n):
            if math.fabs(buff[k]-x[k]) > nr:
                nr = math.fabs(buff[k]-x[k])
                buff[k] = x[k]
        counter = counter+1
        if nr < e:
            break
    for i in range(n):
        print("x", i, " = ", x[i], sep='')
    print("(n=", counter,")", sep='')


def jacobi(a, f, n, e):
    buff = []
    counter = 0
    x = []
    for i in range(n):
        x.append(0.0)
        buff.append(0.0)
    while 1:
        for i in range(n):
            buff[i] = f[i]
            for j in range(n):
                if i != j:
                    buff[i] -= a[i][j]*x[j]
            buff[i] /= a[i][i]
        nr = math.fabs(x[0]-buff[0])
        for i in range(n):
            if math.fabs(x[i]-buff[i])>nr:
                nr = math.fabs(x[i]-buff[i])
            x[i] = buff[i]
        counter = counter + 1
        if nr < e:
            break
    for i in range(n):
        print("x", i, " = ", x[i], sep='')
    print("(n=", counter, ")", sep='')


if __name__ == "__main__":
    A = [[]]
    F = []
    su = []

    n = 0
    e = 0.0001

    with open("matrix.txt") as file:
        su = [list(map(float, row.split())) for row in file.readlines()]
        n = len(su[0])-1
    for i in range(n):
        A.append([]);
        for j in range(n):
            A[i].append(su[i][j])
        F.append(su[i][n])

    print("Jacobi(eps=", e, "):", sep='')
    jacobi(A, F, n, e)

    print("", sep='')

    print("Gauss-Zeidel(eps=", e, "):", sep='')
    gz(A, F, n, e);

