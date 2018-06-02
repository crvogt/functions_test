import numpy as np 

from keras.models import Sequential 
from my_classes_2 import DataGenerator

h = 480
w = 640
chan = 3
#Parameters
params = {'dim': (3, w, h),
		  'batch_size': 1, 
		  'n_channels': 3, 
		  'shuffle': False}

originalDim = h*w
input1 = Input(shape=(h, w, chan))
input2 = Input(shape=(h, w, chan))
input3 = Input(shape=(h, w, chan))
h_q = Dense(512, activation='relu')(inputs)
mu = Dense(n_z, activation='linear')(h_q)
log_sigma = Dense(n_z, activation='linear')(h_q)

#Datasets
partition = #IDs 
labels = #Labels 

#Generators
training_generator = DataGenerator(partition['train'], labels, **params)
validation_generator = DataGenerator(partition['validation'], labels, **params)

#Design Model
model = Sequential()
[...] # Architecture 
model.compile() 

#Train model on dataset 
model.fit_generator(generator=training_generator,
				    validation_data=validation_generator,
				    use_multiprocessing=True,
				    workers=6)

