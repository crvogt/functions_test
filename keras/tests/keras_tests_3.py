
from keras.layers import Dense, Activation, Conv2D, MaxPooling2D, Flatten, Dropout, Input, Embedding, Concatenate
from keras.models import Sequential, Model 
import keras
import numpy as np
import os
from PIL import Image
import sys

#Lets load some data...
dataPath = "/media/carson/WDPassport/deep_learn/keras_tests/images"
imgFiles = os.listdir(dataPath)
for img in imgFiles:
	print img 
	im = Image.open(dataPath+'/'+img);
	im = im.convert(mode='RGB')

#If you want to
#X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=4)

sys.exit()

#We'll have the three input images with accompanying poses
# input_1 = (480, 640, 7)
# input_2 = (480, 640, 7)
# input_3 = (480, 640, 7)
input_1 = (480, 640, 5)
input_2 = (480, 640, 5)
input_3 = (480, 640, 5)
#We can just say for now
#The pose of the new image
# input_4 = (480, 640, 4)
input_4 = (480, 640, 2)

#First Tower
imgInput1 = Input(shape=input_1, name='imgInput1')
l2 = Conv2D(40, (2, 2), padding='valid', activation='relu', input_shape=input_1)(imgInput1)
# l2 = MaxPooling2D((2, 2), padding='same')(l2)
# print l2.shape

#Second Tower
imgInput2 = Input(shape=input_2, name='imgInput2')
k2 = Conv2D(40, (2, 2), padding='valid', activation='relu', input_shape=input_2)(imgInput2)
# k2 = MaxPooling2D((2, 2), padding='same')(k2)
# print k2.shape

#Combining Towers
l3 = keras.layers.concatenate([l2, k2])

imgOutput = Conv2D(3, (3, 3), activation='sigmoid', padding='same', name='output')(l3)
print "Output Shape:"
print imgOutput.shape

model = Model(inputs=[imgInput1, imgInput2, imgInput3], outputs=[imgOutput])
model.compile(optimizer='rmsprop', loss='binary_crossentropy', loss_weights=[1.0])
