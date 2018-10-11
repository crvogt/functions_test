from keras.datasets import mnist 
from keras.layers import Input, Dense, Lambda, Add
from keras.models import Model 
from keras.objectives import binary_crossentropy 
from keras.callbacks import LearningRateScheduler
import keras 

import numpy as np 
import matplotlib.pyplot as plt 
import keras.backend as K 
import tensorflow as tf 

def sample_z(args):
    mu, log_sigma = args
    batch = K.shape(mu)[0]
    dim = K.int_shape(mu)[1]
    eps = K.random_normal(shape=(batch, dim), mean=0, stddev=1.)
    return mu + K.exp(log_sigma / 2) * eps

#Load mnist data
(x_train, y_train), (x_test, y_test) = mnist.load_data()

image_size = x_train.shape[1]
print(x_train.shape)
print(x_test.shape)
original_dim = image_size * image_size
x_train = np.reshape(x_train, [-1, original_dim])
x_test = np.reshape(x_test, [-1, original_dim])
x_train = x_train.astype('float32') / 255
x_test = x_test.astype('float32') / 255




m = 50 
n_z = 8
n_epoch = 2



inputs = Input(shape=(784,))
x1 = Dense(512, activation='relu')(inputs)

mu = Dense(n_z, activation='linear')(x1)
log_sigma = Dense(n_z, activation='linear')(x1)

z = Lambda(sample_z)([mu, log_sigma])

x2 = Dense(512, activation='relu')(z)
x3 = keras.layers.Add()([x1, x2])
outputs = Dense(784, activation='sigmoid')(x3)

vae = Model(inputs, outputs)



#We need to translate our loss into Keras code:
def vae_loss(y_true, y_pred):

    recon = binary_crossentropy(y_true, y_pred)
    recon *= original_dim
    kl = 0.5 * K.sum(-1. - log_sigma + K.exp(log_sigma) + K.square(mu), axis=-1)
    loss = K.mean(kl + recon)
    return loss

#Now train it 
vae.compile(optimizer='adam', loss=vae_loss)
vae.fit(x_train, x_train, epochs=n_epoch, batch_size=m)

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
