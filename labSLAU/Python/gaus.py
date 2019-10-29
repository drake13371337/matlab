def print_mtrx(matr, n, step):
    for i in range(n):
        for j in range(n + step):
            print(matr[i][j], end=' ')
        print()
    print()


def col_max(matrix, a, n):
    maxc = abs(matrix[a][a])
    maxpos = a
    for i in range(a + 1, n):
        element = abs(matrix[i][a])
        if element > maxc:
            maxc = element
            maxpos = i
    return maxpos


def triangle(matrix, n, step):
    buff = 0
    if n == 0:
        return 0
    for i in range(n - 1):
        imax = col_max(matrix, i, n)
        if i != imax:
            for j in range(n + step):
                buff = matrix[i][j]
                matrix[i][j] = matrix[imax][j]
                matrix[imax][j] = buff
        for j in range(i + 1, n):
            mul = 0
            if matrix[i][i] == 0:
                mul = 0
            if matrix[i][i] != 0:
                mul = -matrix[j][i] / matrix[i][i]
            for k in range(i, n + step):
                matrix[j][k] += matrix[i][k] * mul
                if abs(matrix[j][k]) < 0.0001:
                    matrix[j][k] = 0


def rank_matr(matr, n, step):
    rank1 = n;
    chk = 0;
    for i in range(1, n + 1):
        chk = 0
        for j in range(n + step):
            if matr[n - i][j] != 0:
                chk = chk + 1
        if chk == 0:
            rank1 = rank1 - 1
    return rank1


def gauss(matr, rank, n):
    x = []
    for i in range(n):
        x.append(0)
    ranks = rank_matr(matr, n, 1)
    if ranks == rank and ranks < n:
        print("Endless solutions")
        return 0
    if rank == ranks:
        for i in range(1, n + 1):
            x[n - i] = matr[n - i][n]
            for j in range(n):
                if (n - i) != j:
                    x[n - i] = x[n - i] - (matr[n - i][j] * x[j])
            x[n - i] = x[n - i] / matr[n - i][n - i]
            if matr[n - i][n - i] == 0:
                print('x', n - i, " = Endless solutions")
            else:
                print('x', n - i, " = ", x[n - i], sep='')
        return 0
    print("No solutions")


if __name__ == "__main__":
    su = []
    tmp = [[]]
    n = 0

    with open("test.txt") as file:
        su = [list(map(float, row.split())) for row in file.readlines()]
        n = len(su[0])-1
    for i in range(n):
        tmp.append([])
        for j in range(n):
            tmp[i].append(su[i][j])

    print_mtrx(su, n, 1)
    triangle(su, n, 1)
    triangle(tmp, n, 0)
    gauss(su, rank_matr(tmp, n, 0), n)
