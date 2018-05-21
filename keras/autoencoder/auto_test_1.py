from keras.layers import Input, Dense
from keras.models import Model 

from keras.datasets import mnist 
import numpy as np 

import matplotlib.pyplot as plt 

#we'll normalize all values between 0 and 1 and flatten
#the 28x28 images into vectors of size 784
(x_train, _), (x_test, _) = mnist.load_data()

x_train = x_train.astype('float32')/255.
x_test = x_test.astype('float32')/255.
#I think the below can be replaced with "flatten()"
x_train = x_train.reshape((len(x_train), np.prod(x_train.shape[1:])))
x_test = x_test.reshape((len(x_test), np.prod(x_test.shape[1:])))

print x_train.shape
print x_test.shape

numCols = 640
numRows = 480
numChan = 3
inputSize = 784

#This is the size of our encoded representation
#32 floats->compression of factor 24.5, 
#assuming the input is 784 floats
encoding_dim = 32

#This is our input placeholder
input_img = Input(shape=(inputSize,))
#"encoded" is the encoded representation of the input
encoded = Dense(encoding_dim, activation='relu')(input_img)
#"decoded" is the lossy reconstruction of the input
decoded = Dense(inputSize, activation='sigmoid')(encoded)

#This model maps an input to its reconstruction

autoencoder = Model(input_img, decoded)

#Lets also create a separate encoder model 
#This model maps an input to its encoded representation
encoder = Model(input_img, encoded)

#As well as the decoder model 
#Create a placeholder for an encoded (32-dim) input 
encoded_input = Input(shape=(encoding_dim,))
#retrieve the last layer of the autoencoder model 
decoder_layer = autoencoder.layers[-1]
#create the decoder model 
decoder = Model(encoded_input, decoder_layer(encoded_input))

#Lets train our autoencoder to reconstruct MNIST digits
#We'll configure our model to use a per-pixel binary 
#crossentropy loss, and the adadelta optimizer
autoencoder.compile(optimizer='adadelta', loss='binary_crossentropy')

#To preprare our input MNIST data
#See the beginning

#Let's train our autoencoder for 50 epochs
autoencoder.fit(x_train, x_train, epochs=100,
								  batch_size=256,
								  shuffle=True,
								  validation_data=(x_test, x_test))


decoded_imgs = autoencoder.predict(x_test)

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