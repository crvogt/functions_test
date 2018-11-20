import h5py
import numpy as np
from keras.preprocessing import image
from keras.utils.io_utils import HDF5Matrix
import matplotlib.pyplot as plt
from random import randint
import time

fileNameD = '/home/carson/libs/raytrix_gp_data/raytrixImages/darkLF.h5'
fileNameB = '/home/carson/libs/raytrix_gp_data/raytrixImages/lightLF.h5'

with h5py.File(fileNameB, 'r') as hf:
    data = hf['light'][:]

train_len = len(data)
# plt.ion()
counter = 0
while counter < train_len:
	counter = randint(0, train_len-1)
	darkImg = HDF5Matrix(fileNameD, 'dark', start=counter, end=counter+1)
	lightImg = HDF5Matrix(fileNameB, 'light', start=counter, end=counter+1)
	darkImg = np.reshape(darkImg, [100, 100, 3])
	lightImg = np.reshape(lightImg, [100, 100, 3])
    # darkImg = image.load_img(darkImgLoca)
    # darkImg = image.img_to_array(darkImg)
    # darkImg = darkImg/255.

    # lightImg = image.load_img(lightImgLoca)
    # lightImg = image.img_to_array(lightImg)
    # lightImg = lightImg/255.

    # print(lightImg.shape)
    # time.sleep(20)
	fig = plt.figure(figsize=(10, 4))
	fig.add_subplot(1, 2, 1)
	plt.imshow(darkImg)
	fig.add_subplot(1, 2, 2)
	plt.imshow(lightImg)
	plt.show()
	# _ = raw_input("Press [enter] to continue.")
	# time.sleep(2)
	plt.close()
	# counter = counter + 100
