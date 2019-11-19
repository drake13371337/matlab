def func(x):
    return pow((x+pow(x, 3)), 1/2)


def trapeze(a, b, e):
    n = 1
    res = 0
    buff = 0
    while 1:
        h = (b-a)/n
        h1 = h/2
        for i in range(n-1):
            res = res+func(a+h*i)
        for i in range(n*2-1):
            buff = buff+func(a+h1*i)
        res = (res*2+func(a)+func(b))*h/2
        buff = (buff*2+func(a)+func(b))*h1/2
        if abs(buff-res) <= (e*3):
            print("Trapeze: res = ", res, ", n = ", n)
            return 0
        res = 0
        buff = 0
        n += 1


def rectangle(a, b, e):
    n = 1
    trg = 1
    res = 0
    buff = 0
    while trg:
        h = (b-a)/n
        h1 = h/2

        for i in range(0, n-1):
            res = res+func(a+h*i)
        for i in range(0, n*2-1):
            buff = buff+func(a+h1*i)

        res = res*h
        buff = buff*h1

        if abs(buff-res) <= (e*3):
            print("Rectangle(left): res = ", res, ", n = ", n)
            n = 1
            trg = 0
        else:
            n += 1
        res = 0
        buff = 0
    trg = 1
    while trg:
        h = (b-a)/n
        h1 = h/2

        for i in range(n):
            res = res+func(a+h*i);
        for i in range(n*2):
            buff = buff+func(a+h1*i)

        res = res*h
        buff = buff*h1

        if abs(buff-res) <= (e*3):
            print("Rectangle(right): res = ", res, ", n = ", n)
            trg = 0
            n = 1
        else: n += 1
        res = 0
        buff = 0
    trg = 1
    while trg:
        h = (b-a)/n
        h1 = h/2

        for i in range(n-1):
            res = res+func(a+h*i)
        for i in range(n*2-1):
            buff = buff+func(a+h1*i)

        res = (res+(func(a)+func(b))/2)*h
        buff = (buff+(func(a)+func(b))/2)*h1

        if abs(buff-res) <= (e*3):
            print("Rectangle(middle): res = ", res, ", n = ", n)
            trg = 0
        else: n += 1
        res = 0
        buff = 0
    return 0


def simpson(a, b, e):
    n = 1
    res = 0
    buff = 0
    res1 = 0
    buff1 = 0

    while 1:
        h = (b-a)/n/2
        h1 = h/2

        for i in range(n):
            res = res+func(a+h*(2*i-1))
        res = res*4
        for i in range(n-1):
            res1 = res1+func(a+h*2*i)
        res1 = res1*2
        res = res+res1

        for i in range(n*2):
            buff = buff+func(a+h1*(2*i-1))
        buff = buff*4
        for i in range(n*2-1):
            buff1 = buff1+func(a+h1*2*i)
        buff1 = buff1*2
        buff = buff+buff1

        res = (res+func(a)+func(b))*h/3
        buff = (buff+func(a)+func(b))*h1/3

        if abs(buff-res) <= (e*15):
            print("Simpson: res = ", res, ", n = ", n)
            return 0
        res = 0
        buff = 0
        res1 = 0
        buff1 = 0
        n = n+2


if __name__ == "__main__":
    a = 0.6
    b = 1.724
    e = 0.0001

    trapeze(a, b, e)
    rectangle(a, b, e)
    simpson(a, b, e)
