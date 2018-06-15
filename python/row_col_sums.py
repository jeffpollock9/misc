import tensorflow as tf
import numpy as np
import time as tm

n = 500
m = 1000

x = np.random.normal(0.0, 1.0, (n, n)).astype(np.float32)

# apparently tensorflow is row-major so row sums should be faster?

row_sums = tf.reduce_sum(x, 1)
col_sums = tf.reduce_sum(x, 0)

with tf.Session() as sess:

    start = tm.time()

    for i in range(m):
        row_sums_ = sess.run(row_sums)

    print("{} row sums took: {} seconds".format(m, tm.time() - start))

    start = tm.time()

    for i in range(m):
        col_sums_ = sess.run(col_sums)

    print("{} col sums took: {} seconds".format(m, tm.time() - start))
