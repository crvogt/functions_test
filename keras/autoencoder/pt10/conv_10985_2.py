'''

fit_generator ultimately calls train_on_batch which allows for x to be a dictionary.

Also, it could be a list, in which casex is expected to map 1:1 to the inputs defined in Model(input=[in1, ...], ...)

 Note that x could also be a list (one input array per input). Both are allowed.
'''


import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten, Lambda, UpSampling2D
from keras.models import Model, load_model
from keras.preprocessing import image 
import keras.backend as K 
from keras.callbacks import ModelCheckpoint
import matplotlib.pyplot as plt
import numpy as np
import random
import tensorflow as tf
import scipy.misc

import os
from PIL import Image
import sys

# from keras.backend.tensorflow_backend import set_session

# config = tf.ConfigProto()
# config.gpu_options.per_process_gpu_memory_fraction = 1
# config.gpu_options.visible_device_list = "0"
# set_session(tf.Session(config=config))

def get_model_memory_usage(batch_size, model):
	shapes_mem_count = 0
	for l in model.layers:
		single_layer_mem = 1
		for s in l.output_shape:
			if type(s) is tuple:
				s = s[1]
			if s is None:
				continue
			single_layer_mem *= s 
		shapes_mem_count += single_layer_mem

	trainable_count = np.sum([K.count_params(p) for p in set(model.trainable_weights)])
	non_trainable_count = np.sum([K.count_params(p) for p in set(model.non_trainable_weights)])

	total_memory = 4.0*batch_size*(shapes_mem_count + trainable_count + non_trainable_count)
	gbytes = np.round(total_memory / (1024.0 ** 3), 3)
	print('number of gbytes = ' + str(gbytes))
	return gbytes

def sampling(args):
    """Reparameterization trick by sampling fr an isotropic unit Gaussian.
    # Arguments:
        args (tensor): mean and log of variance of Q(z|X)
    # Returns:
        z (tensor): sampled latent vector
    """

    z_mean, z_log_var = args
    batch = K.shape(z_mean)[0]
    dim = K.int_shape(z_mean)[1]
    # by default, random_normal has mean=0 and std=1.0
    epsilon = K.random_normal(shape=(batch, dim))
    return z_mean + K.exp(0.5 * z_log_var) * epsilon

testVal = []

def my_gen():
	'''Generator used by keras.models.sequential.fit_generator
	to yield batches of data. Such a generator is required.
	'''
	'''
	You might try to put everything in a while 1 loop, and make sure everything
	is just constantly shuffling (ie, always a rand set of vertices and internal Points)
	'''
	dataPath = "/home/carson/data_files/all_training_data/"
	batch_size = 2
	batch_count = 0
	vImage1 = [] 
	vImage2 = [] 
	vImage3 = [] 
	vBody = []
	vPose1 = []
	vPose2 = []
	vPose3 = []
	vPoseB = []
	releasedVals = 0

	while 1:
		trainSetIter = random.randint(1,(len(os.listdir(dataPath))))

		vertPath = dataPath + "train_set_" + str(trainSetIter) + "/vertices"
		internalPath = dataPath + "train_set_" + str(trainSetIter) + "/internal_points"

		vertImages = []
		vert1Pose = []
		vert2Pose = []
		vert3Pose = []
		splitResult = []

		for file in os.listdir(vertPath):
		    if file.endswith(".mat") or file.endswith(".txt"):
		    	splitResult = file.split("_")

		resultVec = []
		for file in os.listdir(vertPath):
		    if file.endswith(".mat") or file.endswith(".txt"):
		    	splitResult = file.split(".")
		    	resultVec.append(splitResult[0])

		individualVec = []
		for val in resultVec:
			splitResult = val.split("_")
			individualVec.append(splitResult)
	
		#print(individualVec[0][0])
		vertImages.append(individualVec[0][0]+".jpg")
		vertImages.append(individualVec[1][0]+".jpg")
		vertImages.append(individualVec[2][0]+".jpg")
		# print(vertImages)

		vert1Pose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
		vert1Pose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

		vert2Pose.append(float(individualVec[1][1] + "." + individualVec[1][2]))
		vert2Pose.append(float(individualVec[1][3] + "." + individualVec[1][4]))

		vert3Pose.append(float(individualVec[2][1] + "." + individualVec[2][2]))
		vert3Pose.append(float(individualVec[2][3] + "." + individualVec[2][4]))

		possibleVals = []
		# bodyImg = []
		bodyPose = []
		#Now do this for a random value in the body directory
		for file in os.listdir(internalPath):
		    if file.endswith(".mat") or file.endswith(".txt"):
		    	possibleVals.append(file)

		#Choose random file
		bodyFile = possibleVals[random.randint(0,(len(possibleVals)-1))]

		#Now parse it
		resultVec = []
		splitResult = bodyFile.split(".")
		resultVec.append(splitResult[0])

		individualVec = []
		for val in resultVec:
			splitResult = val.split("_")
			individualVec.append(splitResult)

		bodyImgPath = individualVec[0][0] + ".jpg"

		bodyPose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
		bodyPose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

		#Now we have bodyPose, bodyImg, vert1Pose, vert2Pose, vert3Pose, vertImages
		vertImage1 = image.load_img(vertPath + '/' + vertImages[0])
		vertImage1 = image.img_to_array(vertImage1)
		vertImage1 = vertImage1/255.

		vertImage2 = image.load_img(vertPath + '/' + vertImages[0])
		vertImage2 = image.img_to_array(vertImage1)
		vertImage2 = vertImage1/255.

		vertImage3 = image.load_img(vertPath + '/' + vertImages[0])
		vertImage3 = image.img_to_array(vertImage1)
		vertImage3 = vertImage1/255.

		imgLength = vertImage1.shape[0]*vertImage1.shape[1]*vertImage1.shape[2]
		imgShape = vertImage1.shape
		bodyImg = image.load_img(internalPath + '/' + bodyImgPath)   
		bodyImg = image.img_to_array(bodyImg)
		bodyImg = bodyImg/255.

		#vertImage1 vertImage2 vertImage3 vert1Pose vert2Pose vert3Pose bodyPose bodyImg
		vImage1.append(vertImage1)
		vImage2.append(vertImage2)
		vImage3.append(vertImage3)
		vPose1.append(vert1Pose)
		vPose2.append(vert2Pose)
		vPose3.append(vert3Pose)
		vPoseB.append(bodyPose)
		vBody.append(bodyImg)

		batch_count += 1

		if batch_count == batch_size:
			vImage1 = np.reshape(vImage1, [batch_size, imgShape[0], imgShape[1], imgShape[2]])
			vImage2 = np.reshape(vImage2, [batch_size, imgShape[0], imgShape[1], imgShape[2]])
			vImage3 = np.reshape(vImage3, [batch_size, imgShape[0], imgShape[1], imgShape[2]])
			vBody = np.reshape(vBody, [batch_size, imgShape[0], imgShape[1], imgShape[2]])

			vPose1 = np.reshape(vPose1, [batch_size, 2])
			vPose2 = np.reshape(vPose2, [batch_size, 2])
			vPose3 = np.reshape(vPose3, [batch_size, 2])
			vPoseB = np.reshape(vPoseB, [batch_size, 2])

			inputList = [vImage1, vImage2, vImage3, vPose1, vPose2, vPose3, vPoseB]
			returnTuple = ([inputList, vBody])
			# if releasedVals == 0:
				# print('assigning testVals')
				# print(np.array(vPose1))
				# testVal = [np.array(vImage1), np.array(vImage2), np.array(vImage3), np.array(vPose1), np.array(vPose2), np.array(vPose3), np.array(vPoseB)]
			releasedVals += 1
			print('\nreleasedVals ' + str(releasedVals))
			print('batch_count ' + str(batch_count))
			batch_count = 0
			yield returnTuple
			vImage1 = [] 
			vImage2 = [] 
			vImage3 = [] 
			vBody = []
			vPose1 = []
			vPose2 = []
			vPose3 = []
			vPoseB = []
			inputList = []
			returnTuple = ()
			# batch_count = 0
			
h = 480
w = 640
channels = 3
midDim = 1000
latentDim = 150

#Inputs
image1 = Input(shape=(h, w, channels))
image2 = Input(shape=(h, w, channels))
image3 = Input(shape=(h, w, channels))

pose1 = Input(shape=(2,))
pose2 = Input(shape=(2,))
pose3 = Input(shape=(2,))
pose4 = Input(shape=(2,))

encoder_in = Input(shape=(h,w,channels))
x = Conv2D(64, (5, 5), padding='same', activation='relu')(encoder_in)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(32, (5, 5), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(16, (5, 5), padding='same', activation='relu')(x)
shape = K.int_shape(x)
x = Flatten()(x)

z_mean = Dense(latentDim, name='z_mean')(x)
z_log_var = Dense(latentDim, name='z_log_var')(x)

print(z_mean.shape)
print(z_log_var.shape)

# z = Lambda(sampling, output_shape=(latentDim,), name='z')([z_mean, z_log_var])

encoder_model = Model(encoder_in, [z_mean, z_log_var])

#This ensures the model will be shared, including weights
encoded1 = encoder_model(image1)
encoded2 = encoder_model(image2)
encoded3 = encoder_model(image3)

z1 = Lambda(sampling, output_shape=(latentDim,), name='z1')([encoded1[0], encoded1[1]])
z2 = Lambda(sampling, output_shape=(latentDim,), name='z2')([encoded2[0], encoded2[1]])
z3 = Lambda(sampling, output_shape=(latentDim,), name='z3')([encoded3[0], encoded3[1]])
#Now concatenate
# latent_z = keras.layers.concatenate([encoded1, encoded2, encoded3, pose1, pose2, pose3, pose4])
latent_z = keras.layers.concatenate([z1, z2, z3, pose1, pose2, pose3, pose4])
print('latent_z shape')
print(latent_z.shape)

#Now write the decoder
decoder_in = Dense(shape[1]*shape[2]*shape[3], activation='relu')(latent_z)
x = keras.layers.Reshape((shape[1], shape[2], shape[3]))(decoder_in)
print('decoder in shape')
print(x.shape)
x = Conv2D(16, (7, 7), activation='relu', padding='same')(x)
x = UpSampling2D((2, 2))(x) 
print(x.shape)
x = Conv2D(32, (7, 7), padding='same', activation='relu')(x) 
x = UpSampling2D((2, 2))(x) 
print(x.shape)
x = Conv2D(64, (7, 7), padding='same', activation='relu')(x) 
print(x.shape)
decoder_out = Conv2D(3, (7, 7), activation='sigmoid', padding='same')(x) 
print('decoder out')
print(decoder_out.shape)

ae = Model([image1, image2, image3, pose1, pose2, pose3, pose4], decoder_out)

print('model params = ' + str(ae.count_params()))

get_model_memory_usage(5, ae)

# ae = Model(inputs=[image1, image2, image3], outputs=encoded)
trainGenerator = my_gen()
ae.compile(loss='mse', optimizer='adam')

checkpointer = ModelCheckpoint(filepath='/home/carson/functions_test/keras/autoencoder/pt10/weights.hdf5', verbose=1, save_best_only=True)

ae.fit_generator(trainGenerator, 
			  steps_per_epoch=2,
			  epochs=6000,
			  validation_steps=1)

# ae.save('ae_1.h5')




dataPath = "/home/carson/data_files/all_training_data/"
vImage1 = [] 
vImage2 = [] 
vImage3 = [] 
vBody = []
vPose1 = []
vPose2 = []
vPose3 = []
vPoseB = []
releasedVals = 0


trainSetIter = random.randint(1,(len(os.listdir(dataPath))))

vertPath = dataPath + "train_set_" + str(trainSetIter) + "/vertices"
internalPath = dataPath + "train_set_" + str(trainSetIter) + "/internal_points"

vertImages = []
vert1Pose = []
vert2Pose = []
vert3Pose = []
splitResult = []

for file in os.listdir(vertPath):
    if file.endswith(".mat") or file.endswith(".txt"):
    	splitResult = file.split("_")

resultVec = []
for file in os.listdir(vertPath):
    if file.endswith(".mat") or file.endswith(".txt"):
    	splitResult = file.split(".")
    	resultVec.append(splitResult[0])

individualVec = []
for val in resultVec:
	splitResult = val.split("_")
	individualVec.append(splitResult)

vertImages.append(individualVec[0][0]+".jpg")
vertImages.append(individualVec[1][0]+".jpg")
vertImages.append(individualVec[2][0]+".jpg")

vert1Pose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
vert1Pose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

vert2Pose.append(float(individualVec[1][1] + "." + individualVec[1][2]))
vert2Pose.append(float(individualVec[1][3] + "." + individualVec[1][4]))

vert3Pose.append(float(individualVec[2][1] + "." + individualVec[2][2]))
vert3Pose.append(float(individualVec[2][3] + "." + individualVec[2][4]))

possibleVals = []
bodyPose = []
#Now do this for a random value in the body directory
for file in os.listdir(internalPath):
    if file.endswith(".mat") or file.endswith(".txt"):
    	possibleVals.append(file)

#Choose random file
bodyFile = possibleVals[random.randint(0,(len(possibleVals)-1))]

#Now parse it
resultVec = []
splitResult = bodyFile.split(".")
resultVec.append(splitResult[0])

individualVec = []
for val in resultVec:
	splitResult = val.split("_")
	individualVec.append(splitResult)

bodyPose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
bodyPose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

#Now we have bodyPose, bodyImg, vert1Pose, vert2Pose, vert3Pose, vertImages
vertImage1 = image.load_img(vertPath + '/' + vertImages[0])
vertImage1 = image.img_to_array(vertImage1)
vertImage1 = vertImage1/255.

vertImage2 = image.load_img(vertPath + '/' + vertImages[0])
vertImage2 = image.img_to_array(vertImage1)
vertImage2 = vertImage1/255.

vertImage3 = image.load_img(vertPath + '/' + vertImages[0])
vertImage3 = image.img_to_array(vertImage1)
vertImage3 = vertImage1/255.

imgLength = vertImage1.shape[0]*vertImage1.shape[1]*vertImage1.shape[2]
imgShape = vertImage1.shape

vImage1.append(vertImage1)
vImage2.append(vertImage2)
vImage3.append(vertImage3)
vPose1.append(vert1Pose)
vPose2.append(vert2Pose)
vPose3.append(vert3Pose)
vPoseB.append(bodyPose)

vImage1 = np.reshape(vImage1, [1, imgShape[0], imgShape[1], imgShape[2]])
vImage2 = np.reshape(vImage2, [1, imgShape[0], imgShape[1], imgShape[2]])
vImage3 = np.reshape(vImage3, [1, imgShape[0], imgShape[1], imgShape[2]])
# vBody = np.reshape(vBody, [1, imgShape[0], imgShape[1], imgShape[2]])

vPose1 = np.reshape(vPose1, [1, 2])
vPose2 = np.reshape(vPose2, [1, 2])
vPose3 = np.reshape(vPose3, [1, 2])
vPoseB = np.reshape(vPoseB, [1, 2])

testVal = [vImage1, vImage2, vImage3, vPose1, vPose2, vPose3, vPoseB]

bodyImgPath = individualVec[0][0] + ".jpg"
print(bodyImgPath)
bodyImg = image.load_img(internalPath + '/' + bodyImgPath)   
bodyImg = image.img_to_array(bodyImg)
bodyImg = bodyImg/255.

# print(testVal)
newImage = ae.predict(testVal)
newImage = np.reshape(newImage, [imgShape[0], imgShape[1], imgShape[2]])

scipy.misc.imsave('newImage_6000.jpg', newImage)
# print(newImage.shape)
'''
fig = plt.figure(figsize=(10,4))
fig.add_subplot(1,2,1)
plt.imshow(bodyImg)
fig.add_subplot(1,2,2)
plt.imshow(newImage)
plt.savefig('newImage001.png')
plt.show()
'''
