import tensorflow as tf 
from tensorflow.contrib.data import Dataset, Iterator

#assuming we have two classes in our dataset
NUM_CLASSES = 2

def input_parser(img_path, label):
	#convert the label to one-hot encoding
	print("converting label to one_hot")
	one_hot = tf.one_hot(label, NUM_CLASSES)

	#read the img from file
	print("reading the image from file")
	img_file = tf.read_file(img_path)
	img_decoded = tf.image.decode_image(img_file, channels=3)

	return img_decoded, one_hot

train_imgs = tf.constant(['30.jpg', '31.jpg', '32.jpg',
							'33.jpg', '34.jpg', '35.jpg'])

train_locs = tf.constant([0, 0, 0, 1, 1, 1])

val_imgs = tf.constant(['25.jpg', '1000.jpg'])

val_locs = tf.constant([1, 0])

#Create tf dataset objects
tr_data = tf.data.Dataset.from_tensor_slices((train_imgs, train_locs))
tr_data = tr_data.map(input_parser)
val_data = tf.data.Dataset.from_tensor_slices((val_imgs, val_locs))
val_data = val_data.map(input_parser)

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