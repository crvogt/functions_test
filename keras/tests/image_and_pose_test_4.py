import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
from keras.models import Model 
from keras.preprocessing import image 
import matplotlib.pyplot as plt
import numpy as np

import os
import sys
import random

dataPath = "/home/carson/libs/keras_tests/"

#Choose random file
trainSetIter = random.randint(1,(len(os.listdir(dataPath))))
print(trainSetIter)

intPath = dataPath + "train_set_" + str(trainSetIter) + "/internal_points"
vertPath = dataPath + "train_set_" + str(trainSetIter) + "/vertices"

print(intPath)
print(vertPath)

#List contents of new path 
for val in os.listdir(vertPath):
	print(val)