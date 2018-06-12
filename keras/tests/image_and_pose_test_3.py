import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
from keras.models import Model 
from keras.preprocessing import image 
import matplotlib.pyplot as plt
import numpy as np

import os
import sys
import random

dataPath1 = "/home/carson/libs/keras_tests/train_set_1/vertices/1726.jpg"
dataPath2 = "/home/carson/libs/keras_tests/train_set_1/vertices/758.jpg"

img1 = image.load_img(dataPath1)
img1 = image.img_to_array(img1)
img1 = img1/255.
plt.imshow(img1)
# plt.show()

img2 = image.load_img(dataPath2)
img2 = image.img_to_array(img2)
img2 = img2/255.
plt.imshow(img2)
# plt.show()

inputs = tuple(img1, img2)

print(inputs)