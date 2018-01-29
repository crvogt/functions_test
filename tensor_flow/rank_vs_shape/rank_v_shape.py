import tensorflow as tf 

# a = tf.constant(3.0, dtype=tf.float32)
# b = tf.Variable(5.0, dtype=tf.float32)

# print(a)
# print(b)
# sess = tf.Session()
# sess.run(tf.global_variables_initializer()) 
# print(sess.run(a))
# print(sess.run(b))
# def variableTest():
# 	init = tf.constant_initializer(value=0)
# 	mammal = tf.Variable("Elephant", dtype=tf.string)
# 	ignition = tf.Variable(451, dtype=tf.int16)
# 	floating = tf.Variable(3.14, dtype=tf.float64)
# 	complexNum = tf.Variable((12.3, -4.85), tf.complex)
# 	W = tf.get_variable("W", [10, 30], initializer=init)

# 	print(sess.run(W))
# 	# print(sess.run(mammal))
# 	# print(sess.run(ignition))
# 	# print(sess.run(floating))
# 	# print(sess.run(complexNum))

# with tf.Graph().as_default():
# 	init = tf.global_variables_initializer()
# 	sess = tf.Session()
# 	sess.run(init)
# 	variableTest()

def inference():
	init = tf.constant_initializer(value=0)
	W = tf.get_variable("W", [784, 10], 
							initializer=init)
	# print(sess.run(W))
	b = tf.get_variable("b", [10],
							initializer=init)
	# print(sess.run(b))
	print(W)
	print(b.get_shape())

if __name__ == '__main__':

	with tf.Graph().as_default():
		sess = tf.Session()

		init_op = tf.global_variables_initializer()
		sess.run(init_op)
		inference()

		# #Training cycle
		# for epoch in range(training_epochs):

		# 	avg_cost = 0.
		# 	total_batch = int(mnist.train.num_examples/batch_size)
		# 	#Loop over all batches

		# 	for i in range(total_batch):
		# 		mbatch_x, mbatch_y = mnist.train.next_batch(batch_size)
		# 		#Fit training using batch data
		# 		feed_dict = {x : mbatch_x, y : mbatch_y}
		# 		sess.run(train_op, feed_dict=feed_dict)
		# 		#Compute average loss
		# 		minibatch_cost = sess.run(cost, feed_dict=feed_dict)
		# 		avg_cost += minibatch_cost/total_batch
		# 		#Display logs per epoch step 
		# 	if epoch % display_step == 0:
		# 		# val_feed_dict = {
		# 		# 	x : mnist.validation.images, 
		# 		# 	y : mnist.validation.labels
		# 		# }
		# 		print("Epoch:", '%04d' % (epoch+1), "cost =", "{:.9f}".format(avg_cost))

		# 		# accuracy = sess.run(eval_op, feed_dict=val_feed_dict)
		# 		accuracy = sess.run(eval_op, feed_dict={x: mnist.validation.images, y: mnist.validation.labels})

		# 		print "Validation Error:", (1 - accuracy)

		# 		summary_str = sess.run(summary_op,
		# 								feed_dict=feed_dict)
		# 		summary_writer.add_summary(summary_str, 
		# 									sess.run(global_step))

		# 		saver.save(sess, "logistic_logs/model-checkpoint", 
		# 					global_step=global_step)

		# print "Opimization Finished!"

		# # test_feed_dict = {
		# # 	x : mnist.test.images, 
		# # 	y : mnist.test.labels 
		# # }

		# accuracy = sess.run(eval_op, feed_dict=test_feed_dict)

		# print "Test Accuracy:", accuracy





















# sess = tf.Session()
# #How we create a rank 0 variable
# mammal = tf.Variable("Elephant", dtype=tf.string)
# # print mammal
# ignition = tf.Variable(451, dtype=tf.int16)
# floating = tf.Variable(3.14, dtype=tf.float64)
# complexNum = tf.Variable((12.3, -4.85), tf.complex)

# sess.run(tf.global_variables_initializer())

# print(sess.run(mammal))
# print(sess.run(floating))
 
