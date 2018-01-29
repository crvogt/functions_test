import tensorflow as tf 
import skimage.io as io
import numpy as np 
from matplotlib import pyplot as plt 

IMAGE_HEIGHT = 480 
IMAGE_WIDTH = 640

tfrecords_filename = 'segmentation.tfrecords'

def read_and_decode(filename_queue):
	reader = tf.TFRecordReader()

	_, serialized_example = reader.read(filename_queue)

	features = tf.parse_single_example(
		serialized_example, 
		#Defaults are not specified since both keys are required
		features={
		'height': tf.FixedLenFeature([], tf.int64),
		'width': tf.FixedLenFeature([], tf.int64),
		'image_raw': tf.FixedLenFeature([], tf.string)
		})
	#Convert from a scalar string to a uint8 tensor with shape
	#'mnist.IMAGE_PIXELS'
	image = tf.decode_raw(features['image_raw'], tf.uint8)

	height = tf.cast(features['height'], tf.int32)
	width = tf.cast(features['width'], tf.int32)

	image_shape = tf.stack([height, width, 3])

	image = tf.reshape(image, image_shape)

	image_size_const = tf.constant((IMAGE_HEIGHT, IMAGE_WIDTH, 3), dtype=tf.int32)

	#Random transformations can be put here, before you crop images(?)
	#More information at link in http://warmspringwinds.github.io/tensorflow/tf-slim/2016/12/21/tfrecords-guide/
	resized_image = tf.image.resize_image_with_crop_or_pad(image=image, 
		target_height=IMAGE_HEIGHT, 
		target_width=IMAGE_WIDTH)

	images = tf.train.shuffle_batch(resized_image,
		batch_size=2,
		capacity=30,
		num_threads=2,
		min_after_dequeue=10)
	# print("images tensor")
	# print(images)

	return images

filename_queue = tf.train.string_input_producer(
	[tfrecords_filename], num_epochs=10)

#Even when reading in multiple threads, share the 
#filename queue
image = read_and_decode(filename_queue)

#The op for initializing the variables
init_op = tf.global_variables_initializer()

with tf.Session() as sess:
	sess.run(init_op)

	coord = tf.train.Coordinator()
	threads = tf.train.start_queue_runners(coord=coord)

	#Read of 3 batches for example 
	for i in xrange(3):
		img = sess.run(image)
		print(img[0, :, :, :].shape)

		print('current batch')

		#We selected the batch size of two
		#so we should get two image pairs 
		#in each batch
		#Let's make sure it is random 
		io.imshow(img[0,:, :, :])
		io.show()

		io.imshow(img[1, :, :, :])
		io.show()

	coord.request_stop()
	coord.join(threads)