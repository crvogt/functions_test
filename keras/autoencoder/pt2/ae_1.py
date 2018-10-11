'''

fit_generator ultimately calls train_on_batch which allows for x to be a dictionary.

Also, it could be a list, in which casex is expected to map 1:1 to the inputs defined in Model(input=[in1, ...], ...)

 Note that x could also be a list (one input array per input). Both are allowed.
'''


import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
from keras.models import Model 
from keras.preprocessing import image 
import matplotlib.pyplot as plt
import numpy as np
import random

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
	dataPath = "/home/carson/libs/keras_tests"
	while 1:
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

		possibleVals = []
		bodyImg = []
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

		bodyImg.append(individualVec[0][0]+".jpg")

		bodyPose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
		bodyPose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

		#Now we have bodyPose, bodyImg, vert1Pose, vert2Pose, vert3Pose, vertImages
		imgLength = vertImage1.shape[0]*vertImage1.shape[1]*vertImage1.shape[2]
		vertImage1 = image.load_img(vertImages[0])
	    vertImage1 = image.img_to_array(vertImage1)
	    vertImage1 = vertImage1/255.
	    vertImage2 = image.load_img(vertImages[0])
	    vertImage2 = image.img_to_array(vertImage1)
	    vertImage2 = vertImage1/255.
	    vertImage3 = image.load_img(vertImages[0])
	    vertImage3 = image.img_to_array(vertImage1)
	    vertImage3 = vertImage1/255.

	    bodyImg = image.load_img(bodyImg)   
	    bodyImg = image.img_to_array(bodyImg)
	    bodyImg = bodyImg/255.

	    vertImage1 = np.reshape(vertImage1, [-1, imgLength])
	    vertImage2 = np.reshape(vertImage2, [-1, imgLength])
	    vertImage3 = np.reshape(vertImage3, [-1, imgLength])
	    bodyImg = np.reshape(bodyImg, [-1, imgLength])

	    # yield[vertImage1, vertImage2, vertImage3, bodyImg]
	    # returnList = list(vertImage1, vertImage2, vertImage3, vert1Pose, vert2Pose, vert3Pose, bodyImg, bodyPose)
	    # returnList = tuple([vertImage1, vertImage2, vertImage3, vert1Pose, vert2Pose, vert3Pose, bodyImg, bodyPose])
	    #We want the bodyImg to be the target variable
	    inputList = [vertImage1, vertImage2, vertImage3, vert1Pose, vert2Pose, vert3Pose, bodyPose]
	    returnTuple = ([inputList, bodyImg])
	    yield returnTuple
	    # return returnTuple
	    # return returnList

midDim = 1000
latentDim = 10

encoder_in = Input(shape=(480, 640, 3))
x1 = Conv2D(64, (3, 3), padding='same', activation='relu')(encoder_in)
x2 = MaxPooling2D((2,2))(x1)
x3 = Conv2D(64, (1, 1), padding='same', activation='relu')(x2)
x4 = MaxPooling2D((2,2))(x3)
encoded = Flatten()(x4)
encoder_model = Model(encoder_in, encoded)
print(encoded.shape)

image1 = Input(shape=(480, 640, 3))
image2 = Input(shape=(480, 640, 3))
image3 = Input(shape=(480, 640, 3))

#This ensures the model will be shared, including weights
encoded1 = encoder_model(image1)
encoded2 = encoder_model(image2)
encoded3 = encoder_model(image3)

#Now concatenate
latent_z = keras.layers.concatenate([encoded1, encoded2, encoded3])

#Now add the other inputs to this latent_z

#
fit_generator()
