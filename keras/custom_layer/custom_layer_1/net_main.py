from keras.datasets import mnist
from keras.layers import Input, MaxPooling2D, Conv2D
from keras.layers import UpSampling2D
from keras.models import Model
from keras.layers import Flatten, Reshape
import cv2
from custom_layer import MyLayer
from keras.objectives import binary_crossentropy
from keras.callbacks import LearningRateScheduler
import keras

import numpy as np
import time
import matplotlib.pyplot as plt
import keras.backend as K
import tensorflow as tf

# Load mnist data
(x_train, y_train), (x_test, y_test) = mnist.load_data()

image_size = x_train.shape[1]
# original_dim = image_size * image_size
x_train = np.reshape(x_train, [-1, 28, 28, 1])
x_test = np.reshape(x_test, [-1, 28, 28, 1])
x_train = x_train.astype('float32') / 255
x_test = x_test.astype('float32') / 255

x_train = x_train[0:200, :, :, :]
x_test = x_test[0:20, :, :, :]
y_train = y_train[0:200]
y_test = y_test[0:20]

n_epoch = 10
batch_size = 5

inputs = Input(batch_shape=(batch_size, 28, 28, 1))

output = Conv2D(1, (3, 3), activation='relu', padding='same')(inputs)
output = MaxPooling2D((2, 2))(output)
output = Conv2D(20, (3, 3), activation='relu', padding='same')(output)
output = MaxPooling2D((2, 2))(output)
output = Conv2D(20, (3, 3), activation='relu', padding='same')(output)
output = UpSampling2D((2, 2))(output)
output = Conv2D(20, (3, 3), activation='relu', padding='same')(output)
output = UpSampling2D((2, 2))(output)
output = Conv2D(1, (3, 3), activation='relu', padding='same')(output)
output_dim = (batch_size, 28, 28, 1)
output = Flatten()(output)
print(output.shape)
output_dim = output.shape
output = MyLayer(784, output_dim)(output)
output = Reshape((28, 28, 1))(output)
# time.sleep(20)
print(output.shape)
# time.sleep(20)


# Now train it
vae = Model(inputs=inputs, output=output)
vae.compile(optimizer='adam', loss='mse')
vae.summary()
vae.fit(x_train, x_train, epochs=n_epoch, batch_size=batch_size)


# Try to get weights
# weights = vae
layer = vae.get_layer(index=11)
gotten_weights = layer.get_weights()
# print(layer.get_weights())
weights = gotten_weights[0]
print(weights)
print(weights.shape)

# print(weights)

decoded_imgs = vae.predict(x_test[0:5, :, :, :])
print(decoded_imgs.shape)
decoded_imgs = np.reshape(decoded_imgs, [-1, 28, 28, 1])
#
print(decoded_imgs.shape)
cv2.imshow("eh", decoded_imgs[0, :, :, :])
cv2.waitKey(2000)
# # How many digits we will display
# n = 10
# plt.figure(figsize=(20, 4))
# for i in range(n):
#     # display original
#     ax = plt.subplot(2, n, i + 1)
#     plt.imshow(x_test[i].reshape(28, 28))
#     plt.gray()
#     ax.get_xaxis().set_visible(False)
#     ax.get_yaxis().set_visible(False)
#
#     # display reconstruction
#     ax = plt.subplot(2, n, i + 1 + n)
#     plt.imshow(decoded_imgs[i].reshape(28, 28))
#     plt.gray()
#     ax.get_xaxis().set_visible(False)
#     ax.get_yaxis().set_visible(False)
# plt.savefig('7_auto_test_7.png')
# plt.show()
