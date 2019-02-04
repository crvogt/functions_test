import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['figure.figsize'] = (7,7) # Make the figures a bit bigger

from keras.datasets import mnist
from keras.models import Model
from keras.models import Input
from keras.layers import Dropout
from keras.layers.core import Dense, Dropout, Activation
from keras.utils import np_utils
import keras
from custom_layer import MyLayer

nb_classes = 10

# the data, shuffled and split between tran and test sets
(X_train, y_train), (X_test, y_test) = mnist.load_data()

X_train = X_train.reshape(60000, 784)
X_test = X_test.reshape(10000, 784)
X_train = X_train.astype('float32')
X_test = X_test.astype('float32')
X_train /= 255
X_test /= 255

Y_train = np_utils.to_categorical(y_train, nb_classes)
Y_test = np_utils.to_categorical(y_test, nb_classes)

inputs = Input(shape=(784,))
output = Dense(512, activation='relu')(inputs)
output = Dropout(0.2)(output)
output = Dense(512, activation='relu')(output)
output = Dropout(0.2)(output)
output = MyLayer(512)(output)
output = Dropout(0.2)(output)
output = Dense(10, activation='softmax')(output)

model = Model(inputs=inputs, output=output)
cust_adam = keras.optimizers.Adam(lr=0.003, beta_1=0.9, beta_2=0.999, epsilon=None, decay=0.001)
model.compile(loss='categorical_crossentropy', optimizer=cust_adam)
model.summary()

model.fit(X_train, Y_train, batch_size=8, nb_epoch=2,
          verbose=1, validation_data=(X_test, Y_test))

layer = model.get_layer(index=5)
weights = layer.get_weights()[0]
print(weights)
print(weights.shape)

score = model.evaluate(X_test, Y_test,
                       verbose=1)
print('\n', score)
# print('Test score: ', score[0])
# print('Test accuracy: ', score[1])
