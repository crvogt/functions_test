'''

fit_generator ultimately calls train_on_batch which allows for x to be a dictionary.

Also, it could be a list, in which casex is expected to map 1:1 to the inputs defined in Model(input=[in1, ...], ...)

 Note that x could also be a list (one input array per input). Both are allowed.
'''


import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten, Lambda, UpSampling2D
from keras.models import Model 
from keras.preprocessing import image 
import keras.backend as K 
import matplotlib.pyplot as plt
import numpy as np
import random
import tensorflow as tf

import os
from PIL import Image
import sys

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

def my_gen():
	'''Generator used by keras.models.sequential.fit_generator
	to yield batches of data. Such a generator is required.
	'''
	'''
	You might try to put everything in a while 1 loop, and make sure everything
	is just constantly shuffling (ie, always a rand set of vertices and internal Points)
	'''
	dataPath = "/home/carson/libs/keras_tests/"
	batch_count = 0

	while batch_count < 5:
		trainSetIter = random.randint(1,(len(os.listdir(dataPath))))

		vertPath = dataPath + "train_set_" + str(trainSetIter) + "/vertices"
		internalPath = dataPath + "train_set_" + str(trainSetIter) + "/internal_points"

		vertImages = []
		#Now get the positions, starting with theta
		vert1Pose = []
		vert2Pose = []
		vert3Pose = []
		splitResult = []

		for file in os.listdir(vertPath):
		    if file.endswith(".mat"):
		    	splitResult = file.split("_")

		resultVec = []
		for file in os.listdir(vertPath):
		    if file.endswith(".mat"):
		    	splitResult = file.split(".")
		    	resultVec.append(splitResult[0])

		individualVec = []
		for val in resultVec:
			splitResult = val.split("_")
			individualVec.append(splitResult)

		vertImages.append(individualVec[0][0]+".jpg")
		vertImages.append(individualVec[1][0]+".jpg")
		vertImages.append(individualVec[2][0]+".jpg")
		print(vertImages)

		vert1Pose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
		vert1Pose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

		vert2Pose.append(float(individualVec[1][1] + "." + individualVec[1][2]))
		vert2Pose.append(float(individualVec[1][3] + "." + individualVec[1][4]))

		vert3Pose.append(float(individualVec[2][1] + "." + individualVec[2][2]))
		vert3Pose.append(float(individualVec[2][3] + "." + individualVec[2][4]))

		print(vert2Pose)

		possibleVals = []
		# bodyImg = []
		bodyPose = []
		#Now do this for a random value in the body directory
		for file in os.listdir(internalPath):
		    if file.endswith(".mat"):
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
		# print(bodyImgPath)

		bodyPose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
		bodyPose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

		#Now we have bodyPose, bodyImg, vert1Pose, vert2Pose, vert3Pose, vertImages
		vertImage1 = image.load_img(vertPath + '/' + vertImages[0], grayscale=True)
		vertImage1 = image.img_to_array(vertImage1)
		vertImage1 = vertImage1/255.

		vertImage2 = image.load_img(vertPath + '/' + vertImages[0], grayscale=True)
		vertImage2 = image.img_to_array(vertImage1)
		vertImage2 = vertImage1/255.

		vertImage3 = image.load_img(vertPath + '/' + vertImages[0], grayscale=True)
		vertImage3 = image.img_to_array(vertImage1)
		vertImage3 = vertImage1/255.

		imgLength = vertImage1.shape[0]*vertImage1.shape[1]*vertImage1.shape[2]
		imgShape = vertImage1.shape
		bodyImg = image.load_img(internalPath + '/' + bodyImgPath, grayscale=True)   
		bodyImg = image.img_to_array(bodyImg)
		bodyImg = bodyImg/255.

		# vertImage1 = np.reshape(vertImage1, [-1, imgLength])
		vertImage1 = np.reshape(vertImage1, [1, imgShape[0], imgShape[1], imgShape[2]])
		vertImage2 = np.reshape(vertImage2, [1, imgShape[0], imgShape[1], imgShape[2]])
		vertImage3 = np.reshape(vertImage3, [1, imgShape[0], imgShape[1], imgShape[2]])
		bodyImg = np.reshape(bodyImg, [1, imgShape[0], imgShape[1], imgShape[2]])
		print('bodyImg shape')
		print(bodyImg.shape)

		vert1Pose = np.array(vert1Pose).reshape(1, 2)
		vert2Pose = np.array(vert2Pose).reshape(1, 2)
		print(vert2Pose.shape)
		vert3Pose = np.array(vert3Pose).reshape(1, 2)
		print(vert3Pose.shape)
		bodyPose = np.array(bodyPose).reshape(1, 2)
		print(bodyPose.shape)
		# bodyImg = np.array(bodyImg)

		inputList = [vertImage1, vertImage2, vertImage3, vert1Pose, vert2Pose, vert3Pose, bodyPose]
		returnTuple = ([inputList, bodyImg])
		yield returnTuple
		inputList = []
		returnTuple = ()
		batch_count += 1

h = 480
w = 640
channels = 1
midDim = 1000
latentDim = 10

#Inputs
image1 = Input(shape=(h, w, channels))
image2 = Input(shape=(h, w, channels))
image3 = Input(shape=(h, w, channels))

pose1 = Input(shape=(2,))
pose2 = Input(shape=(2,))
pose3 = Input(shape=(2,))
pose4 = Input(shape=(2,))

encoder_in = Input(shape=(h,w,channels))
x = Conv2D(6, (3, 3), padding='same', activation='relu')(encoder_in)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(8, (1, 1), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(10, (1, 1), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(12, (1, 1), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(20, (1, 1), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
# x = keras.layers.Reshape((1400,))(x)
print('pre flatten shape')
shape = K.int_shape(x)
print(shape)
x = Flatten()(x)
# print(x.shape)

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
# z1 = Lambda(sampling, output_shape=(latentDim,), name='z')([encoded1[0], encoded1[1]])
print('encoded1 shape(0)')
print(encoded1[0].shape)
# print('z shape')
# print(z.shape)
z1 = Lambda(sampling, output_shape=(latentDim,), name='z1')([encoded1[0], encoded1[1]])
z2 = Lambda(sampling, output_shape=(latentDim,), name='z2')([encoded2[0], encoded2[1]])
z3 = Lambda(sampling, output_shape=(latentDim,), name='z3')([encoded3[0], encoded3[1]])
#Now concatenate
# latent_z = keras.layers.concatenate([encoded1, encoded2, encoded3, pose1, pose2, pose3, pose4])
latent_z = keras.layers.concatenate([z1, z2, z3, pose1, pose2, pose3, pose4])
print('latent_z shape')
print(latent_z.shape)
#Now write the decoder
# reshaped = keras.layers.Reshape((576008,))(latent_z)
# decoder_in = Dense(midDim, activation='relu')(reshaped)
print('shape shape')
print(shape)
decoder_in = Dense(shape[1]*shape[2]*shape[3], activation='relu')(latent_z)
x = keras.layers.Reshape((shape[1], shape[2], shape[3]))(decoder_in)
print('decoder in shape')
print(x.shape)
x = Conv2D(20, (3, 3), activation='relu', padding='same')(x) # (8, 8)
x = UpSampling2D((2, 2))(x) # (16, 16)
print('upsample 1')
print(x.shape)
x = Conv2D(12, (1, 1), activation='relu')(x) # (14, 14)
x = UpSampling2D((2, 2))(x) # (28, 28)
print(x.shape)
x = Conv2D(16, (3, 3), padding='same', activation='relu')(x) # (14, 14)
x = UpSampling2D((8, 8))(x) # (28, 28)
print(x.shape)
decoder_out = Conv2D(1, (3, 3), activation='sigmoid', padding='same')(x) # (100, 100)
print('decoder out')
print(decoder_out.shape)

ae = Model([image1, image2, image3, pose1, pose2, pose3, pose4], decoder_out)
# ae = Model(inputs=[image1, image2, image3], outputs=encoded)
trainGenerator = my_gen()
ae.compile(loss='mse', optimizer='adam')

ae.fit_generator(trainGenerator, 
			  steps_per_epoch=1,
			  epochs=5,
			  validation_steps=1)