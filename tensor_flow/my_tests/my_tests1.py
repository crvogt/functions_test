import tensorflow as tf 
import skimage.io as io 
import numpy as np 

# IMAGE_HEIGHT = 480 
# IMAGE_WIDTH = 640

'''
prior to input layer...
load data sets
split into Training and Validation 
batch

Input layer
7 values
Pose_new image1, pose1, image2, pose2, image3, pose3

convolution net

output layer
image_new
'''
# def load_data():

# def split_data():
# 	#Make batchable

# def decode_image(img):
# 	reconstructed_img = 
# original_images = []

# img_path = '1000.jpg'

# img = np.array(io.imread(img_path))

# #We have to know sizes of images to later
# #read raw serialized string, 
# #convert to 1d array and convert to 
# #respective shape that image used to have
# height = img.shape[0]
# width = img.shape[1]

# #Put in the original images 
# #just to check for correctness
# original_images.append(img)


# img_raw = img.tostring()

# # example = tf.train.Example(features=tf.train.Features(feature={
# # 	'height': _int64_feature(height),
# # 	'width': _int64_feature(width), 
# # 	'image_raw': _bytes_feature(img_raw)}))

pose = [3., 4., 5., 0.1, 0.2, 0.3, 0.4]
img_orig = tf.read_file('1000.jpg')

pose_tensor = tf.Variable(pose, dtype=tf.float64, name='Pose')
img_tensor = tf.image.decode_jpeg(img_orig, name='Image')
# tensor_list = tf.concat(img_tensor, pose_tensor)
gray_img_tensor = tf.image.rgb_to_grayscale(img_tensor)
dims = tf.shape(gray_img_tensor)
height = dims[0] 
width = dims[1]
reshaped_img = tf.reshape(gray_img_tensor,[dims[0]*dims[1]])

reshaped_reconstruct_img = tf.reshape(reshaped_img, [height, width, 1])
#Try creating a batch
tensor_list = [reshaped_img, pose_tensor]
# tensor_batch = tf.train.batch(tensor_list, batch_size=1)

img_recon = tf.image.encode_jpeg(img_tensor)
img_reshape_gray = tf.image.encode_jpeg(reshaped_reconstruct_img)
write_image = tf.write_file('1000_mod.jpg', img_recon)
write_image = tf.write_file('1000_gray.jpg', img_reshape_gray)
# img_tensor = tf.image.decode_jpeg(img_raw,channels=3)

with tf.Session() as sess:
	sess.run(tf.global_variables_initializer())
	print(sess.run(img_tensor))
	print(sess.run(tf.shape(img_tensor)))	
	sess.run(write_image)
	# print(sess.run(pose_tensor))
	print("pose_tensor shape: ")
	print(sess.run(tf.shape(pose_tensor)))
	print("pose tensor rank: ")
	print(sess.run(tf.rank(pose_tensor)))
	
	print("tensor data types:")
	print("Pose: ")
	print(pose_tensor)
	print(pose_tensor.dtype)
	print("Image: ")
	print(sess.run(img_tensor))
	print(img_tensor.dtype)
	print(sess.run(tf.shape(gray_img_tensor)))
	print(sess.run(dims))

	print("dims[0]")
	print(sess.run(dims[0]))
	print("dims[1]")
	print(sess.run(dims[1]))

	print("reshaped_img shape:")
	print(sess.run(tf.shape(reshaped_img)))
	print("rank")
	print(sess.run(tf.rank(reshaped_img)))

	print(sess.run(tensor_list))

# plt.show()