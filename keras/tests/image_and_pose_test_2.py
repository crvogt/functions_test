import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
from keras.models import Model 
from keras.preprocessing import image 
import matplotlib.pyplot as plt
import numpy as np

import os
import sys
import random

dataPath = "/home/carson/libs/keras_tests/train_set_1/vertices/"
vertImages = []
#Now get the positions, starting with theta
vert1Pose = []
vert2Pose = []
vert3Pose = []
splitResult = []

for file in os.listdir(dataPath):
    if file.endswith(".mat"):
    	splitResult = file.split("_")

resultVec = []
for file in os.listdir(dataPath):
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

print(vert1Pose)
print(vert2Pose)
print(vert3Pose)

possibleVals = []
bodyImg = []
bodyPose = []
#Now do this for a random value in the body directory
dataPath = "/home/carson/libs/keras_tests/train_set_1/internal_points/"
for file in os.listdir(dataPath):
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

print(bodyImg)
# print(bodyImg.shape)
print(bodyPose)
# print(bodyPose.shape)
