import tensorflow as tf

tf.enable_eager_execution()

# single value in a matrix
indices = tf.constant([[0, 0]], tf.int32)
values = tf.constant([3.14], tf.float32)
shape = tf.constant([3, 3], tf.int32)

print(tf.scatter_nd(indices, values, shape))

# index for each value in a 3x3 matrix
indices = tf.constant([[0, 0], [1, 1], [2, 2]], tf.int32)
values = tf.constant([3.14, 666.0, 1.0], tf.float32)
shape = tf.constant([3, 3], tf.int32)

print(tf.scatter_nd(indices, values, shape))

# 1 index for all values in a 4x3 matrix (will fill rows)
indices = tf.constant([1], tf.int32)
values = tf.constant([[3.14, 666.0, 1.0]], tf.float32)
shape = tf.constant([4, 3], tf.int32)

print(tf.scatter_nd(indices, values, shape))

# somewhat generic code for putting values in the diagnonal and off diagonals
n = tf.constant(4, tf.int32)
p = tf.constant(2, tf.int32)

diag_values = tf.fill([n], tf.constant(3.14, tf.float32))
diag_indices = tf.tile(tf.expand_dims(tf.range(n), -1),  (1, 2))

p_range = tf.expand_dims(tf.range(p), 1)
p_block = tf.concat([p_range, p_range + p], 1)

off_diag_indices = tf.concat([p_block, tf.reverse(p_block, [1])], 0)
off_diag_values = tf.fill([2 * p], tf.constant(42.0, tf.float32))

indices = tf.concat([diag_indices, off_diag_indices], 0)
values = tf.concat([diag_values, off_diag_values], 0)
shape = tf.stack([n, n])

print(tf.scatter_nd(indices, values, shape))
