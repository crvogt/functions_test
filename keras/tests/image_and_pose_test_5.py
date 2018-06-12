import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
from keras.models import Model 
from keras.preprocessing import image 
import matplotlib.pyplot as plt
import numpy as np

import os
import sys
import random

vertImage = image.load_img("/home/carson/libs/keras_tests/train_set_1/vertices/758.jpg")

vertImage = image.img_to_array(vertImage)
vertImage = vertImage/255.

imgLength = vertImage.shape[0]*vertImage.shape[1]*vertImage.shape[2]
print(vertImage.shape)
print(imgLength)
vertImage = np.reshape(vertImage, [-1 , imgLength])
print(vertImage.shape) #(1, 921600)