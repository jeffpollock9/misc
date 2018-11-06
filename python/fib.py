
def fib_rec(n):
    """"Fibonacci using recursion"""

    if n < 3:
        return n

    return fib_rec(n - 1) + fib_rec(n - 2)


def fib_for(n):
    """Fibonacci using a for loop"""

    if n < 3:
        return n

    a = 1
    b = 2

    for _ in range(n - 1):
        c = a + b
        a = b
        b = c

    return a


for n in range(10):
    print("{}: rec: {}, for: {}".format(n, fib_rec(n), fib_for(n)))
