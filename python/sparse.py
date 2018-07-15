import tensorflow as tf
import time as tm
import numpy as np

"""Silly play with sparse matmul with diagonal matrix"""

n = 2000

i = tf.expand_dims(tf.range(n), 1)
j = tf.expand_dims(tf.range(n), 1)

indices = tf.concat([i, j], 1)
values = tf.fill([n], 42.0)

x = tf.constant(np.random.normal(0.0, 1.0, [n, n]), tf.float32)

dense = tf.scatter_nd(indices, values, [n, n])
sparse = tf.SparseTensor(tf.cast(indices, tf.int64),
                         values, tf.constant([n, n], tf.int64))

dense_mul = tf.matmul(dense, x)
dense_a_is_sparse_mul = tf.matmul(dense, x, a_is_sparse=True)
sparse_mul = tf.sparse_tensor_dense_matmul(sparse, x)

with tf.Session() as sess:

    dense_, sparse_ = sess.run([dense, sparse])

    dense_mul_ = sess.run(dense_mul)
    dense_a_is_sparse_mul_ = sess.run(dense_a_is_sparse_mul)
    sparse_mul_ = sess.run(sparse_mul)

assert np.allclose(dense_mul_, dense_a_is_sparse_mul_)
assert np.allclose(dense_mul_, sparse_mul_)


def run(op, name, n=100):

    start = tm.time()

    for i in range(n):
        sess.run(op)

    end = tm.time()

    print("{} {} took {} seconds".format(n, name, end - start))


with tf.Session() as sess:

    run(dense_mul, "dense_mul")
    run(dense_a_is_sparse_mul, "dense_a_is_sparse_mul")
    run(sparse_mul, "sparse_mul")
