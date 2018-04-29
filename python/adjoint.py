import tensorflow as tf
import time as tm

n = 500
m = 1000

tf.set_random_seed(42)

a = tf.random_uniform((n, n))
b = tf.random_uniform((n, n))

transpose = tf.matmul(a, b, transpose_b=True)
adjoint = tf.matmul(a, b, adjoint_b=True)

assertion = tf.assert_equal(transpose, adjoint)

with tf.Session() as sess:

    sess.run(assertion)

    start = tm.time()
    for _ in range(m):
        _ = sess.run(transpose)
    print("transpose took {} seconds".format(tm.time() - start))

    start = tm.time()
    for _ in range(m):
        _ = sess.run(adjoint)
    print("adjoint took {} seconds".format(tm.time() - start))
