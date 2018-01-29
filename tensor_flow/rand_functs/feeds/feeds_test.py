import tensorflow as tf

x_ = [5, 6, 7, 8]
y_ = [5, 6, 7, 8]

input1 = tf.placeholder(tf.float32)
input2 = tf.placeholder(tf.float32)
output = tf.multiply(input1, input2)

with tf.Session() as sess:
	for i in range(len(x_)):
		print(sess.run([output], feed_dict={input1:x_, input2:y_}))