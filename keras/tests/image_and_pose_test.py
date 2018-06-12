import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
from keras.models import Model 
from keras.preprocessing import image 
import matplotlib.pyplot as plt
import numpy as np

import os
import sys	

# while 1:
	#Load images
	#Lets load some data...
dataPath = "/home/carson/libs/keras_tests/train_set_1/vertices/"
vertImages = []
for file in os.listdir(dataPath):
    if file.endswith(".jpg"):
    	newfile = os.path.join(dataPath, file)
        img = image.load_img(newfile)
        x = image.img_to_array(img)
        x = x/255.
        # plt.imshow(x)
        # plt.show()
        vertImages.append(x)

print(dataPath[-5:-3])

counter = 0
for i in dataPath:
	if i == "_":
		print(dataPath[counter-1])
	counter += 1

#Try to get the image names
vertNames = []
counter = 0
v = ""
for file in os.listdir(dataPath):
    if file.endswith(".mat"):
    	print(file)
    	for val in file:
    		if val != "_":
    			v += val
    		else:
				vertNames.append(v+".jpg")
				v = ""
				break

#Now get the positions, starting with theta
vert1Pose = []
vert2Pose = []
vert3Pose = []
v = ""
for file in os.listdir(dataPath):
	if file.endswith(".mat"):
		counter = 0
		record = False
		for val in file:
			if val == '_'

		
for values in vertNames:
	newfile = os.path.join(dataPath, values)
	img = image.load_img(newfile)
	x = image.img_to_array(img)
	x = x/255.
	plt.imshow(x)
	print("showing " + newfile)
	plt.show()
    	# print(file)
    	# newfile = os.path.join(dataPath, file)
     #    img = image.load_img(newfile)
     #    x = image.img_to_array(img)
     #    x = x/255.
     #    # plt.imshow(x)
     #    # plt.show()
     #    vertImages.append(x)

# for image in vertImages:
# 	plt.imshow(image)
# 	plt.show()

# img = image.load_img(dataPath)
# print(type(img))

# x = image.img_to_array(img)
# print(type(x))
# print(x.shape)
# plt.imshow(x/255.)
# plt.show()
	# imgFiles = os.listdir(dataPath)
	# for img in imgFiles:
	# 	print img 
	# 	im = Image.open(dataPath+'/'+img);
	# 	im = im.convert(mode='RGB')