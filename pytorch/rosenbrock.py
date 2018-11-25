import torch

"""rosenbrock optimisation
see: https://en.wikipedia.org/wiki/Rosenbrock_function
optimum is at (a, a**2) with function value 0, usually a=1 and b=100
"""

a = torch.tensor(1.0)
b = torch.tensor(100.0)


def rosenbrock(x, y):
    return (a - x)**2 + b * (y - x**2)**2


"""adam"""

torch.manual_seed(42)

x = torch.randn(1, requires_grad=True)
y = torch.randn(1, requires_grad=True)

adam = torch.optim.Adam([x, y], lr=0.1)

for step in range(10_001):
    adam.zero_grad()
    f = rosenbrock(x, y)
    f.backward()
    adam.step()
    if step % 2_500 == 0 or step == 10_000:
        print("adam step: {}\n\tf: {}\n\tx: {}\n\ty: {}".format(step, f, x, y))


"""lbfgs"""

torch.manual_seed(42)

x = torch.randn(1, requires_grad=True)
y = torch.randn(1, requires_grad=True)

lbfgs = torch.optim.LBFGS([x, y], max_iter=1000)


def closure():
    lbfgs.zero_grad()
    f = rosenbrock(x, y)
    f.backward()
    return f


lbfgs.step(closure)
print("done lbfgs\n\tf: {}\n\tx: {}\n\ty: {}".format(closure(), x, y))
