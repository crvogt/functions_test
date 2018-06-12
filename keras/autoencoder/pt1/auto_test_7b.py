from keras.datasets import mnist 
from keras.layers import Input, Dense, Lambda
from keras.models import Model 
from keras.objectives import binary_crossentropy 
from keras.callbacks import LearningRateScheduler
import keras 

import numpy as np 
import matplotlib.pyplot as plt 
import keras.backend as K 
import tensorflow as tf 

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
n_epoch = 50

#First, we implement the encoder net Q(z|X) which takes input X and outputs two
#things, mu and Sigma X, the parameters of the Gaussian 
inputs = Input(shape=(784,))
h_q = Dense(512, activation='relu')(inputs)
mu = Dense(n_z, activation='linear')(h_q)
log_sigma = Dense(n_z, activation='linear')(h_q)

'''
Reparameterization Trick
How do we get z from the encoder outputs?
WE could sample z from a Gaussian, whose parameters are the outputs
of the encoder. But this won't work if we want to train with gradient
descent as the sampling operation doesn't have a gradient

The reparameterization trick makes the network differentiable.
Basically it diverts the non-differentiable operation out of the network, so that
even though we still involve a thing that is non-differentiable, at least it is out
of the network, hence the network could still be trained.

As follows: if we have x~N(mu, Sig) and standardize it so that mu = 0 and Sig = 1, 
we could revert it back to the original distribution by reverting the standardization 
process, hence we have 
x=mu + Sig 1/2 x_std

We can extend this if we sample from a standard normal ddistribution
we could vconvert it to any Gaussian we want if we know the mean and the variance. 
Hence, we could implement our sampling operation of z by:
z=mu(X) + Sig 1/2(X)eps
where eps ~ N(0,1)

During backpropagation we don't care about the sampling process, as it is now
outsie the network ie it doesn't depend on anything in the net hence the gradient won't
 flow through it 
 '''
def sample_z(args):
    mu, log_sigma = args
    batch = K.shape(mu)[0]
    dim = K.int_shape(mu)[1]
    eps = K.random_normal(shape=(batch, dim), mean=0, stddev=1.)
    return mu + K.exp(log_sigma / 2) * eps

#sample z ~ Q(z|X)
z = Lambda(sample_z)([mu, log_sigma])

#Now we create the decoder net P(X|z):
decoder_hidden = Dense(512, activation='relu')
decoder_out = Dense(784, activation='sigmoid')

h_p = decoder_hidden(z)
outputs = decoder_out(h_p)

#Lastly, from this model, we can do three things: reconstruct inputs,
#encode inputs into latent variables and generate data from latent variables
#so we have three Keras models:

#Overall VAE model, for reconstruction and training 
vae = Model(inputs, outputs)

#Encoder model, to encode input into latent variable 
#we use the mean as the output as it is the center point, the representative
#of the gaussian 
encoder = Model(inputs, [mu, log_sigma])

#Generator model, generate new data given latent variable z 
d_in = Input(shape=(n_z,))
d_h = decoder_hidden(d_in)
d_out = decoder_out(d_h)
decoder = Model(d_in, d_out)

#We need to translate our loss into Keras code:
def vae_loss(y_true, y_pred):
	#Calculate loss = reconstruction loss + kl loss for each data in minibatch
	#E(log P(X|z))
	# recon = K.sum(K.binary_crossentropy(y_pred, y_true), axis=1)
    recon = binary_crossentropy(y_true, y_pred)
    recon *= original_dim
	#D_KL(Q(z|X) || P(z|X)); calculate in closed form as both dist are Gaussian 
	# kl = 0.5 * K.sum(K.exp(log_sigma) + K.square(mu) - 1. - log_sigma, axis=1)
    kl = 0.5 * K.sum(-1. - log_sigma + K.exp(log_sigma) + K.square(mu), axis=-1)
    loss = K.mean(kl + recon)
	
    # return recon + kl
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
