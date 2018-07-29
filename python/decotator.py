
def print_args(func):

    def _print_args(*args, **kwargs):
        print("args: {}".format(args))
        print("kwargs: {}".format(kwargs))

        ret = func(*args, **kwargs)

        return ret

    return _print_args


@print_args
def foo(*args, **kwargs):
    return args, kwargs


bar = foo(1, 2, x=1, y=2)
