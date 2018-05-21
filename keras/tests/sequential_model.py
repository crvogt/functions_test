from keras.models import Sequential
from keras.layers import Dense, Activation

#Create a simple model by passing a list of layer instances
#to the constructor
model = Sequential([
	Dense(32, input_shape=(784,)),
	Activation('relu'),
	Dense(10),
	Activation('softmax'),
])

#You can also simply add layers via the .add() method
model = Sequential()
model.add(Dense(32, input_dim=784))
model.add(Activation('relu'))

	
