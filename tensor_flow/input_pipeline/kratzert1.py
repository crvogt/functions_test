import tensorflow as tf 
from tensorflow.contrib.data import Dataset, Iterator

train_imgs = tf.constant(['30.jpg', '31.jpg', '32.jpg',
							'33.jpg', '34.jpg', '35.jpg'])

train_locs = tf.constant([0, 0, 0, 1, 1, 1])

val_imgs = tf.constant(['25.jpg', '1000.jpg'])

val_locs = tf.constant([1, 0])

#Create tf dataset objects
tr_data = Dataset.from_tensor_slices((train_imgs, train_locs))
val_data = Dataset.from_tensor_slices((val_imgs, val_locs))

#Create a tf iterator object
iterator = Iterator.from_structure(tr_data.output_types, 
										tr_data.output_shapes)
next_element = iterator.get_next()

#Create two initialization operations to switch between datasets
training_init_op = iterator.make_initializer(tr_data)
validation_init_op = iterator.make_initializer(val_data)

with tf.Session() as sess:

	#Initialize the iterator on the training data 
	sess.run(training_init_op)

	#get each element of the training dataset until the end is reached
	while True:
		try:
			elem = sess.run(next_element)
			print(elem)
		except tf.errors.OutOfRangeError:
			print("End of training dataset...")
			break

	#Initialize the iterator on the validation data 
	sess.run(validation_init_op)

	#get each element of the validation dataset until end 
	while True:
		try:
			elem = sess.run(next_element)
			print(elem)
		except tf.errors.OutOfRangeError:
			print("End of training dataset....")
			break