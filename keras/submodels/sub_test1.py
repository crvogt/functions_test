'''
This network is meant to be a simple test of submodels
'''

from keras.preprocessing import image
from random import randint
from keras.models import Model
from keras.layers import Input, Conv2D, MaxPooling2D
import keras.backend as K
from keras.utils.io_utils import HDF5Matrix
import numpy as np
import h5py
import params
import utilities
from keras.callbacks import TensorBoard, ModelCheckpoint
import matplotlib.pyplot as plt
import time
from scipy.interpolate import RectBivariateSpline
# from time import time

def DataGenerator():
    fileNameBright = '/home/carson/libs/raytrix_gp_data/raytrixImages/lightLF.h5'
    fileNameDark = '/home/carson/libs/raytrix_gp_data/raytrixImages/darkLF.h5'
    with h5py.File(fileNameBright, 'r') as hf:
        data = hf['light'][:]

    train_len = len(data)
    batch_size = 4

    while True:
        fileName = params.h5Location
        x1 = randint(0, train_len-batch_size)
        x_cur = HDF5Matrix(fileNameDark, 'dark', start=x1, end=x1+batch_size)
        y_cur = HDF5Matrix(fileNameBright, 'light', start=x1, end=x1+batch_size)
        yield x_cur, y_cur

def net(inputImg):
    cLayer1 = Conv2D(32, (3, 3), padding='same', activation='relu')(inputImg)
    cLayer1 = Conv2D(32, (3, 3), padding='same', activation='relu')(cLayer1)

    cLayer2 = Conv2D(64, (3, 3), padding='same', activation='relu')(cLayer1)
    cLayer2 = Conv2D(64, (3, 3), padding='same', activation='relu')(cLayer2)

    cLayer3 = Conv2D(128, (3, 3), padding='same', activation='relu')(cLayer2)
    cLayer3 = Conv2D(128, (3, 3), padding='same', activation='relu')(cLayer3)

    cLayer4 = Conv2D(64, (3, 3), padding='same', activation='relu')(cLayer3)
    cLayer4 = Conv2D(64, (3, 3), padding='same', activation='relu')(cLayer4)

    cLayer5 = Conv2D(32, (3, 3), padding='same', activation='relu')(cLayer4)
    cLayer5 = Conv2D(32, (3, 3), padding='same', activation='relu')(cLayer5)
    cLayer5 = Conv2D(3, (3, 3), padding='same', activation='sigmoid')(cLayer5)

    return cLayer5#Model(inputImg, cLayer5)


trainingGenerator = DataGenerator()

# Depth Model
HEIGHT = params.saiHEIGHT
WIDTH = params.saiWIDTH
CHANNELS = params.saiCHANNELS

dConvInput1 = Input(shape=(HEIGHT, WIDTH, CHANNELS))

# dConvOutput1 = net(dConvInput1)
submodel1 = Model(dConvInput1, net(dConvInput1))
submodel2 = Model(submodel1.output, net(submodel1.output))

# dConvInput2 = Input(shape=(HEIGHT, WIDTH, CHANNELS))
# dConvOutput2 = net(dConvOutput1)
# submodel2 = Model(net(dConvInput1), dConvOutput1)

fullModel = Model(dConvInput1, net(net(dConvInput1)))

fullModel.compile(optimizer='adam', loss='mean_squared_error')

# tensorboard = TensorBoard(log_dir="/home/carson/libs/tb/logs/{}".format(time()))
# checkpointer = ModelCheckpoint(filepath=params.modelLocation, monitor='loss', verbose=1, save_best_only=True)

# print(fullModel.summary())

history = fullModel.fit_generator(generator=trainingGenerator,
                    epochs=100,
                    shuffle='batch',
                    steps_per_epoch=8,
                    use_multiprocessing=False,
                    max_queue_size=1)