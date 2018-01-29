from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

import tensorflow as tf 

#None means the dimension can be any length
x = tf.placeholder(tf.float32, [None, 784])
learning_rate = 0.5

#Variable is a modifiable tensor
#Model parameters are generally variables
W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))

#Since we're going to learn W and b
#It doesn't matter much what they are initially

y = tf.nn.softmax(tf.matmul(x, W) + b)

#Implementing cross-entropy
y_ = tf.placeholder(tf.float32, [None, 10])

#Now we can implement the cross entropy function
cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y), reduction_indices=[1]))
#tf.log computes the log of each y element
#tf.reduce_sum adds the elements in the second dimension of
#y, due to the reduction_indices=[1] parameter
#tf.reduce_mean computes the mean over all the examples in the batch

train_step = tf.train.GradientDescentOptimizer(learning_rate).minimize(cross_entropy)

sess = tf.InteractiveSession()
tf.global_variables_initializer().run()

#We'll run the training step 1000 times
for _ in range(10000):
	batch_xs, batch_ys = mnist.train.next_batch(100)
	sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})

correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))
