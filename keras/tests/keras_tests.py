from keras.datasets import mnist
from matplotlib import pyplot as plt

#Load pre-shuffled MNIST data into train and test sets
(X_train, y_train), (X_test, y_test) = mnist.load_data()

print X_train.shape

plt.imshow(X_train[0])

plt.show()