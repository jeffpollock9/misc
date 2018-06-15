import hello_boost_python as hbp
import numpy as np


if __name__ == '__main__':

    print("greet() = {}".format(hbp.greet()))

    print("\n*** d = {{1: 2, 3: 4}} ***")
    d = {1: 2, 3: 4}
    c = hbp.copy_dict(d)
    print("keys(d) = {}".format(hbp.keys(d)))
    print("c = copy_dict(d), print(c) = {}".format(c))

    print("\n*** l = [1, 2, 3] ***")
    l = [1, 2, 3]
    print("list_plus(l, 1) = {}".format(hbp.list_plus(l, 1)))
    print("none_plus(l) = {}".format(hbp.none_list(l)))

    print("\n*** v = IntVector(), v.append(1), 2, 3... ***")
    v = hbp.IntVector()
    v.append(1)
    v.append(2)
    v.append(3)
    print("int_vector_plus(v, 2) = {}".format(
        [tmp for tmp in hbp.int_vector_plus(v, 2)]))

    print("\n*** a = np.array([1.0, 2.0, 3.0]) ***")
    a = np.array([1.0, 2.0, 3.0])
    print("array_plus(a, 2.0) = {}".format(hbp.array_plus(a, 2.0)))

    print("\n*** foo1 = foo('foo1'), foo2 = foo() ***")
    foo1 = hbp.foo("foo1")
    foo2 = hbp.foo()
    print("foo1.bar() = {}".format(foo1.bar()))
    print("foo1.readwrite_msg = {}".format(foo1.readwrite_msg))
    print("foo1.readonly_msg = {}".format(foo1.readonly_msg))

    print("\n*** equality ***:")
    print("foo1.rand() = {}\nfoo2.rand() = {}".format(
        foo1.rand(), foo2.rand()))

    print("foo1 < foo2 = {}".format(foo1 < foo2))
    print("foo1 == foo2 = {}".format(foo1 == foo2))
    print("foo1 > foo2 = {}".format(foo1 > foo2))

    print("\n*** addition ***:")
    print("((foo1 + foo2).bar() = {}".format(((foo1 + foo2).bar())))

    print("\n*** cast to int ***:")
    print("int(foo1) = {}".format(int(foo1)))

    print("\n*** cast to str ***:")
    print("str(foo1) = {}".format(str(foo1)))

    print("\n*** oops() ***:")
    hbp.oops()
