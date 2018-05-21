from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Convolution2D, MaxPooling2D
from keras.utils import np_utils
from keras.preprocessing.image import img_to_array

import numpy as np
import os
from PIL import Image

#input image dimensions
w,h = 640,480

#If we do this directly, we run out of memory very quickly
dataPath = "/media/carson/WDPassport/deep_learn/pr2_dataset/set_1"

x=[]
y=[]
imgCount = 0;

#Looks like you might want to put images in their own folder
imgFiles = os.listdir(dataPath)
for img in imgFiles:
	print img
	im = Image.open(dataPath+'/'+img);
	im = im.convert(mode='RGB')
	imrs=im.resize((w,h))
	imrs=img_to_array(imrs)/255
	imrs=imrs.transpose(2,0,1)
	imrs=imrs.reshape(3,w,h)
	x.append(imrs)
	# y.append(fol)
	imgCount = imgCount + 1
	# print imgCount

batch_size = 32
nb_epoch = 20
nb_filters = 32
nb_pool = 2
nb_conv = 3

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=4)

uniques, id_train=np.unique(y_train, return_inverse=True)
Y_train=np_utils.to_categorical(id_train, nb_classes)

#So, lets define the model
model = Sequential()
model.add(Convolution2D(nb_filters, nb_conv, nb_conv, border_mode='same', input_shape=x_train.shape[1:]))
model.add(Activation('relu'));
model.add(Convolution2D(nb_filters, nb_conv, nb_conv))
model.add(Activation('relu'))
model.add(MaxPooling2D(pool_size=(nb_pool, nb_pool)))
model.add(Dropout(0.5))
model.add(Flatten())
model.add(Dense(nb_classes))
model.add(Activation('softmax'));
model.compile(loss='categorical_crossentropy', optimizer='adadelta', metrics=['accuracy'])

nb_epoch = 1
batch_size = 5
model.fit(x_train, Y_train, batch_size=batch_size, nb_epoch=nb_epoch, verbose=1, validation_data=(x_test, Y_test)
