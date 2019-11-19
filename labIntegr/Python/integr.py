def func(x):
    return pow((x+pow(x, 3)), 1/2)


def trapeze(a, b, e):
    n = 1
    res = 0
    buff = 0
    while 1:
        h = (b-a)/n
        for i in range(1, n-1):
            res = res+func(a+h*i)
        res = (res*2+func(a)+func(b))*h/2
        if abs(buff-res) <= (e*3):
            print("Trapeze: res = ", res, ", n = ", n, ", e = ", e)
            return 0
        buff = res
        res = 0
        n += 1


def rectangle(a, b, e):
    n = 2
    trg = 1
    res = 0
    buff = 0
    while trg:
        h = (b-a)/n

        for i in range(n-1):
            res = res+func(a+h*i)

        res = res*h

        if abs(buff-res) <= (e*3):
            print("Rectangle(left): res = ", res, ", n = ", n, ", e = ", e)
            n = 1
            trg = 0
        else:
            n += 1
        buff = res
        res = 0
    trg = 1
    while trg:
        h = (b-a)/n

        for i in range(1, n):
            res = res+func(a+h*i)

        res = res*h

        if abs(buff-res) <= (e*3):
            print("Rectangle(right): res = ", res, ", n = ", n, ", e = ", e)
            trg = 0
            n = 1
        else:
            n += 1
        buff = res
        res = 0
    trg = 1
    while trg:
        h = (b-a)/n

        for i in range(1, n-1):
            res = res+func(a+h*i)

        res = (res+(func(a)+func(b))/2)*h

        if abs(buff-res) <= (e*3):
            print("Rectangle(middle): res = ", res, ", n = ", n, ", e = ", e)
            trg = 0
        else:
            n += 1
        buff = res
        res = 0
    return 0


def simpson(a, b, e):
    n = 2
    res = 0
    buff = 0
    res1 = 0

    while 1:
        h = (b-a)/n/2

        for i in range(1, n):
            res = res+func(a+h*(2*i-1))
        res = res*4
        for i in range(1, n-1):
            res1 = res1+func(a+h*2*i)
        res1 = res1*2
        res = res+res1

        res = (res+func(a)+func(b))*h/3

        if abs(buff-res) <= (e*15):
            print("Simpson: res = ", res, ", n = ", n, ", e = ", e)
            return 0
        buff = res
        res = 0
        res1 = 0
        n = n+2


if __name__ == "__main__":
    a = 0.6
    b = 1.724
    e = 0.0001
    e1 = 0.00001

    trapeze(a, b, e)
    rectangle(a, b, e)
    simpson(a, b, e)
    print(" ")
    trapeze(a, b, e1)
    rectangle(a, b, e1)
    simpson(a, b, e1)
