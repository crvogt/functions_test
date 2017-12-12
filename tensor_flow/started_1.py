from __future__ import print_function
import tensorflow as tf 

node1 = tf.constant(3.0, dtype=tf.float32)
node2 = tf.constant(4.0) # also tf.float32 implicitly
print(node1, node2)

sess = tf.Session()
print(sess.run([node1, node2]))

node3 = tf.add(node1, node2)
print("node3:", node3)
print("sess.run(node3):", sess.run(node3))

a = tf.placeholder(tf.float32)
b = tf.placeholder(tf.float32)
adder_node = a + b # + provides a shortcut for tf.add(a,b)

print(sess.run(adder_node, {a: 3, b:4.5}))
print(sess.run(adder_node, {a: [1,3], b:[2, 4]}))

add_and_triple = adder_node * 3.
print(sess.run(add_and_triple, {a: 3, b: 4.5}))

W = tf.Variable([.3], dtype = tf.float32)
b = tf.Variable([-.3], dtype=tf.float32)
x = tf.placeholder(tf.float32)
linear_model = W*x + b

#Constants are initialized when you call tf.constant, and their value can never
#change. By contras, variables are not initialized when you call tf.Variable
#To initialize all the variables in a TensorFlow program, you must explicitly 
#call a special operation as follows:

#DOESN'T WORK - MUST INITIALIZE FIRST
# print("Before initializer-")
# print("W: ", sess.run(W))
# print("b: ", sess.run(b))

init = tf.global_variables_initializer()
sess.run(init)

# print("After initializer-")
# print("W: ", sess.run(W))
# print("b: ", sess.run(b))

#Until we call sess.run, the variables are inunitialized
#Since x is a placeholder, we can evaluate linear_model for several values of x simultaneously as follows
# print(sess.run(linear_model, {x: [1, 2, 3, 4]}))

y = tf.placeholder(tf.float32)
squared_deltas = tf.square(linear_model - y)
loss = tf.reduce_sum(squared_deltas)
# print(sess.run(loss, {x: [1, 2, 3, 4], y:[0, -1, -2, -3]}))

#tf.assign allows us to change a variables value
# fixW = tf.assign(W, [-1.])
# fixb = tf.assign(b, [1.])
# sess.run([fixW, fixb])
# print(sess.run(loss, {x:[1, 2, 3, 4], y:[0, -1, -2, -3]}))

#tf.train API
optimizer = tf.train.GradientDescentOptimizer(0.01)
train = optimizer.minimize(loss)

sess.run(init) #reset values to incorrect defaults
for i in range(1000):
	sess.run(train, {x: [1, 2, 3, 4], y: [0, -1, -2, -3]})

print(sess.run([b, W]))