'''

fit_generator ultimately calls train_on_batch which allows for x to be a dictionary.

Also, it could be a list, in which casex is expected to map 1:1 to the inputs defined in Model(input=[in1, ...], ...)

 Note that x could also be a list (one input array per input). Both are allowed.
'''


import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
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

	while batch_count < 1:
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

		bodyImg = image.load_img(internalPath + '/' + bodyImgPath)   
		bodyImg = image.img_to_array(bodyImg)
		bodyImg = bodyImg/255.

		vertImage1 = np.reshape(vertImage1, [-1, imgLength])
		vertImage2 = np.reshape(vertImage2, [-1, imgLength])
		vertImage3 = np.reshape(vertImage3, [-1, imgLength])
		bodyImg = np.reshape(bodyImg, [-1, imgLength])

		vertImage1 = np.array(vertImage1)
		vertImage2 = np.array(vertImage2)
		vertImage3 = np.array(vertImage3)
		vert1Pose = np.array(vert1Pose).reshape(1, 2)
		vert2Pose = np.array(vert2Pose).reshape(1, 2)
		print(vert2Pose.shape)
		vert3Pose = np.array(vert3Pose).reshape(1, 2)
		print(vert3Pose.shape)
		bodyPose = np.array(bodyPose).reshape(1, 2)
		print(bodyPose.shape)
		bodyImg = np.array(bodyImg)

		inputList = [vertImage1, vertImage2, vertImage3, vert1Pose, vert2Pose, vert3Pose, bodyPose]
		returnTuple = ([inputList, bodyImg])
		yield returnTuple
		inputList = []
		returnTuple = ()
		batch_count += 1

originalDim = 921600
midDim = 1000
latentDim = 10

encoder_in = Input(shape=(921600,))
x = Dense(midDim, activation='relu')(encoder_in)
encoded = Dense(latentDim, activation='relu')(x)

encoder_model = Model(encoder_in, encoded)
# print(encoded.shape)

image1 = Input(shape=(921600,))
image2 = Input(shape=(921600,))
image3 = Input(shape=(921600,))

#This ensures the model will be shared, including weights
encoded1 = encoder_model(image1)
encoded2 = encoder_model(image2)
encoded3 = encoder_model(image3)

#Try and get poses
pose1 = Input(shape=(2,))
pose2 = Input(shape=(2,))
pose3 = Input(shape=(2,))
pose4 = Input(shape=(2,))

#Now concatenate
latent_z = keras.layers.concatenate([encoded1, encoded2, encoded3, pose1, pose2, pose3, pose4])

#Now add the other inputs to this latent_z

#Now write the decoder
decoder_in = Dense(midDim, activation='relu')(latent_z)
decoder_out = Dense(921600, activation='sigmoid')(decoder_in)

# decoder_model = Model(latent_z, decoder_out)

ae = Model([image1, image2, image3, pose1, pose2, pose3, pose4], decoder_out)
# ae = Model(inputs=[image1, image2, image3], outputs=encoded)
trainGenerator = my_gen()
ae.compile(loss='mse', optimizer='adam')

ae.fit_generator(trainGenerator, 
			  steps_per_epoch=1,
			  epochs=1,
			  validation_steps=1)