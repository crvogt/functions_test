import keras 
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Flatten
from keras.models import Model 

midDim = 1000
latentDim = 10

encoder_in = Input(shape=(480, 640, 3))
x = Conv2D(64, (3, 3), padding='same', activation='relu')(encoder_in)
x = MaxPooling2D((2,2))(x)
x = Conv2D(64, (1, 1), padding='same', activation='relu')(x)
x = MaxPooling2D((2,2))(x)
encoded = Flatten()(x)
encoder_model = Model(encoder_in, encoded)
print(encoded.shape)

image1 = Input(shape=(480, 640, 3))
image2 = Input(shape=(480, 640, 3))
image3 = Input(shape=(480, 640, 3))

#This ensures the model will be shared, including weights
encoded1 = encoder_model(image1)
encoded2 = encoder_model(image2)
encoded3 = encoder_model(image3)

#Now concatenate
latent_z = keras.layers.concatenate([encoded1, encoded2, encoded3])

#Now add the other inputs to this latent_z

