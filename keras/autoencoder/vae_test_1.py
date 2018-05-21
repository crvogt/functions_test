from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

from keras.layers import Flatten, Lambda, Input, Dense, Conv2D, MaxPooling2D, Reshape, UpSampling2D
from keras.models import Model 
from keras.datasets import mnist
from keras.losses import mse, binary_crossentropy
from keras.utils import plot_model
from keras import backend as K 

import keras
import numpy as np 
import matplotlib.pyplot as plt 
import argparse 
import os

def sampling(args):
	'''
	Reparameterization trick by sampling from an isotropic unit Gaussian.
	Args:
		args(tensor): mean and log of variance of Q(z|X)
	Returns:
		z(tensor): sampled latent vector
	'''
	z_mean, z_log_var = args 
	batch = K.shape(z_mean)[0]
	dim = K.int_shape(z_mean)[1]
	# By default, random_normal has mean=0 and std=1.0
	epsilon = K.random_normal(shape=(batch, dim))
	return z_mean + K.exp(0.5 * z_log_var) * epsilon

#import mnist data
(x_train, y_train), (x_test, y_test) = mnist.load_data()

image_size = x_train.shape[1]
original_dim = image_size*image_size
# x_train = np.reshape(x_train, [-1, original_dim])
# x_test = np.reshape(x_test, [-1, original_dim])
x_train = x_train.astype('float32')/255.
x_test = x_test.astype('float32')/255.

#network params
latent_dim = 2
batch_size = 100
epochs = 5
# input_shape = (original_dim,)
input_shape = (28, 28, 1)

# encoder
inputs = Input(shape=input_shape, name='encoder_input')
print(inputs.shape)
x = Conv2D(16, (3, 3), activation='relu', padding='same')(inputs) #Should go 28x28x1 -> 14x14x16
x = MaxPooling2D((2, 2), padding='same')(x)
x = Conv2D(32, (3, 3), activation='relu', padding='same')(x) #Should go 14x14x16 -> 7x7x32
x = MaxPooling2D((2, 2), padding='same')(x)
reshaped_encoded = Flatten()(x)
z_mean = Dense(latent_dim, name='z_mean')(reshaped_encoded)
z_log_var = Dense(latent_dim, name='z_log_var')(reshaped_encoded)
z = Lambda(sampling, output_shape=(latent_dim,), name='z')([z_mean, z_log_var])

# decoder
latent_inputs = Input(shape=(latent_dim,), name='z_sampling')
x = Dense(8 * 8)(latent_inputs)
x = Reshape([8, 8, 1])(x)
x = Conv2D(8, (3, 3), activation='relu', padding='same')(x) # (8, 8)
x = UpSampling2D((2, 2))(x) # (16, 16)
x = Conv2D(16, (3, 3), activation='relu')(x) # (14, 14)
x = UpSampling2D((2, 2))(x) # (28, 28)
output_img = Conv2D(1, (3, 3), activation='sigmoid', padding='same')(x) # (28, 28)

# Prepare Models
encoder = Model(inputs, [z_mean, z_log_var, z], name='encoder')
# encoder.summary()

decoder = Model(latent_inputs, output_img, name='decoder')
# decoder.summary()

# Instantiate VAE model
#These two seem to be equivalent
# print(decoder(encoder(inputs)[2]))
# print(output_img)

outputs = decoder(encoder(inputs)[2]) 
vae = Model(inputs, outputs, name='vae_mlp')



models = (encoder, decoder)
data = (x_test, y_test)
reconstruction_loss = binary_crossentropy(inputs, outputs)

reconstruction_loss *= original_dim
kl_loss = 1 + z_log_var - K.square(z_mean) - K.exp(z_log_var)
kl_loss = K.sum(kl_loss, axis=-1)
kl_loss *= -0.5

vae_loss = K.mean(reconstruction_loss + kl_loss)
vae.add_loss(vae_loss)
vae.compile(optimizer='adam')
vae.summary()

#train the autoencoder
vae.fit(x_train,
		epochs=epochs,
		batch_size=batch_size,
		validation_data=(x_test, None))

decoded_imgs = vae.predict(x_test)

#How many digits we will display
n = 10 
plt.figure(figsize=(20, 4))
for i in range(n):
    #display original
    ax = plt.subplot(2, n, i + 1)
    plt.imshow(x_test[i].reshape(28, 28))
    plt.gray()
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)

    #display reconstruction
    ax = plt.subplot(2, n, i + 1 + n)
    plt.imshow(decoded_imgs[i].reshape(28, 28))
    plt.gray()
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
plt.show()