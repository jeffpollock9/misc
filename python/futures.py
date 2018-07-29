import concurrent.futures as cf
import multiprocessing as mp
import time as tm


def f(x):
    tm.sleep(1)
    return x + 10


x = range(4)

start = tm.time()

with cf.ThreadPoolExecutor() as executor:
    results = [y for y in executor.map(f, x)]

end = tm.time()

print("cf finished in {:.2f} second(s)".format(end - start))
print(results)

start = tm.time()

with mp.Pool(mp.cpu_count()) as pool:
    results = pool.map(f, x)

end = tm.time()

print("mp finished in {:.2f} second(s)".format(end - start))
print(results)
