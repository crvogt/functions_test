import numpy as np 
import skimage.io as io 
import tensorflow as tf 
from matplotlib import pyplot as plt

filenames = [('1000.jpg'), ('25.jpg'), ('30.jpg'), 
	('31.jpg'), ('32.jpg'), ('33.jpg'), ('34.jpg'), 
	('35.jpg'), ('36.jpg'), ('37.jpg'), ('38.jpg')]

def _bytes_feature(value):
	return tf.train.Feature(bytes_list=tf.train.BytesList(value=[value]))

def _int64_feature(value):
	return tf.train.Feature(int64_list=tf.train.Int64List(value=[value]))

tfrecords_filename = 'segmentation.tfrecords'

writer = tf.python_io.TFRecordWriter(tfrecords_filename)

#Let's collect the real images to later on compare
#to the reconstructed ones
original_images = []

for img_path in filenames:
	img = np.array(io.imread(img_path))

	#We have to know sizes of images to later
	#read raw serialized string, 
	#convert to 1d array and convert to 
	#respective shape that image used to have
	height = img.shape[0]
	width = img.shape[1]

	#Put in the original images 
	#just to check for correctness
	original_images.append(img)

	img_raw = img.tostring()

	example = tf.train.Example(features=tf.train.Features(feature={
		'height': _int64_feature(height),
		'width': _int64_feature(width), 
		'image_raw': _bytes_feature(img_raw)}))

	writer.write(example.SerializeToString())

writer.close()

reconstructed_images = []

record_iterator = tf.python_io.tf_record_iterator(path=tfrecords_filename)

for string_record in record_iterator:
	example = tf.train.Example()
	example.ParseFromString(string_record)

	height = int(example.features.feature['height'].int64_list.value[0])
	width = int(example.features.feature['width'].int64_list.value[0])
	img_string = (example.features.feature['image_raw'].bytes_list.value[0])
	print("height:")
	print height
	print("width:")
	print width
	img_1d = np.fromstring(img_string, dtype=np.uint8)
	reconstructed_img = img_1d.reshape((height, width, -1))

	reconstructed_images.append((reconstructed_img))

#Check if the reconstructed images match
#the original images 

print("Number of original images:")
print(len(original_images))
for original_pair, reconstructed_pair in zip(original_images, reconstructed_images):
	if(np.allclose(original_pair, reconstructed_pair)):
		print("woo x 2")

print("done")
# for original_pair, reconstructed_pair in zip(original_images, reconstructed_images):
	
# 	img_pair_to_compare = zip(original_pair, reconstructed_pair)

# 	# if(np.allclose(original_pair, reconstructed_pair)):
# 	# 	print("Images agree!")

# 	# io.imshow(original_pair)
# 	# io.imshow(reconstructed_pair)
# 	# # plt.show()