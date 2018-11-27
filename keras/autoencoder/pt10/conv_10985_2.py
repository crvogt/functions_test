'''

fit_generator ultimately calls train_on_batch which allows for x to be a dictionary.

Also, it could be a list, in which casex is expected to map 1:1 to the inputs defined in Model(input=[in1, ...], ...)

 Note that x could also be a list (one input array per input). Both are allowed.
'''


import keras 
from keras.layers import Input, Conv2D, MaxPooling2D
from keras.layers import Dense, Flatten, Lambda, UpSampling2D
from keras.layers import concatenate
from keras.models import Model, load_model
from keras.preprocessing import image 
import keras.backend as K 
from keras.callbacks import ModelCheckpoint
import matplotlib.pyplot as plt
import numpy as np
import random
import tensorflow as tf
import scipy.misc

import os
from PIL import Image
import sys
import time

# from keras.backend.tensorflow_backend import set_session

# config = tf.ConfigProto()
# config.gpu_options.per_process_gpu_memory_fraction = 1
# config.gpu_options.visible_device_list = "0"
# set_session(tf.Session(config=config))

def get_model_memory_usage(batch_size, model):
    shapes_mem_count = 0
    for l in model.layers:
        single_layer_mem = 1
        for s in l.output_shape:
            if type(s) is tuple:
                s = s[1]
            if s is None:
                continue
            single_layer_mem *= s
        shapes_mem_count += single_layer_mem

    trainable_count = np.sum([K.count_params(p) for p in set(model.trainable_weights)])
    non_trainable_count = np.sum([K.count_params(p) for p in set(model.non_trainable_weights)])

    total_memory = 4.0*batch_size*(shapes_mem_count + trainable_count + non_trainable_count)
    gbytes = np.round(total_memory / (1024.0 ** 3), 3)
    print('number of gbytes = ' + str(gbytes))
    return gbytes

def concat_dims(args):
    poseCatC, zC = args
    concated = keras.layers.concatenate([poseCatC, zC])
    return concated


def sampling(args):
    """Reparameterization trick by sampling fr an isotropic unit Gaussian.
    # Arguments:
        args (tensor): mean and log of variance of Q(z|X)
    # Returns:
        z (tensor): sampled latent vector
    """

    z_mean, z_log_var = args
    print('z_mean shape')
    print(z_mean.shape)
    print('z_log_var shape')
    print(z_log_var.shape)
    # time.sleep(2)
    batch = K.shape(z_mean)[0]
    dim = K.int_shape(z_mean)[1]
    # by default, random_normal has mean=0 and std=1.0
    epsilon = K.random_normal(shape=(batch, dim))
    f = K.exp(0.5*z_log_var)
    print('f shape')
    print(K.shape(f))
    # time.sleep(20)
    return z_mean + K.exp(0.5 * z_log_var) * epsilon

testVal = []


def my_gen():
    '''Generator used by keras.models.sequential.fit_generator
    to yield batches of data. Such a generator is required.
    '''
    '''
    You might try to put everything in a while 1 loop, and make sure everything
    is just constantly shuffling (ie, always a rand set of vertices and internal Points)
    '''
    dataPath = "/home/carson/libs/keras_tests/"
    batch_size = 4
    batch_count = 0
    vImage1 = []
    vImage2 = []
    vImage3 = []
    vBody = []
    vPose1 = []
    vPose2 = []
    vPose3 = []
    vPoseB = []
    releasedVals = 0

    while 1:
        trainSetIter = random.randint(1,(len(os.listdir(dataPath))))

        vertPath = dataPath + "train_set_" + str(trainSetIter) + "/vertices"
        internalPath = dataPath + "train_set_" + str(trainSetIter) + "/internal_points"

        vertImages = []
        vert1Pose = []
        vert2Pose = []
        vert3Pose = []
        splitResult = []

        for file in os.listdir(vertPath):
            if file.endswith(".mat") or file.endswith(".txt"):
                splitResult = file.split("_")

        resultVec = []
        for file in os.listdir(vertPath):
            if file.endswith(".mat") or file.endswith(".txt"):
                splitResult = file.split(".")
                resultVec.append(splitResult[0])

        individualVec = []
        for val in resultVec:
            splitResult = val.split("_")
            individualVec.append(splitResult)

        # print(individualVec[0][0])
        vertImages.append(individualVec[0][0]+".jpg")
        vertImages.append(individualVec[1][0]+".jpg")
        vertImages.append(individualVec[2][0]+".jpg")
        # print(vertImages)

        vert1Pose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
        vert1Pose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

        vert2Pose.append(float(individualVec[1][1] + "." + individualVec[1][2]))
        vert2Pose.append(float(individualVec[1][3] + "." + individualVec[1][4]))

        vert3Pose.append(float(individualVec[2][1] + "." + individualVec[2][2]))
        vert3Pose.append(float(individualVec[2][3] + "." + individualVec[2][4]))

        possibleVals = []
        # bodyImg = []
        bodyPose = []
        # Now do this for a random value in the body directory
        for file in os.listdir(internalPath):
            if file.endswith(".mat") or file.endswith(".txt"):
                possibleVals.append(file)

        # Choose random file
        bodyFile = possibleVals[random.randint(0,(len(possibleVals)-1))]

        # Now parse it
        resultVec = []
        splitResult = bodyFile.split(".")
        resultVec.append(splitResult[0])

        individualVec = []
        for val in resultVec:
            splitResult = val.split("_")
            individualVec.append(splitResult)

        bodyImgPath = individualVec[0][0] + ".jpg"

        bodyPose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
        bodyPose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

        # Now we have bodyPose, bodyImg, vert1Pose, vert2Pose, vert3Pose, vertImages
        vertImage1 = image.load_img(vertPath + '/' + vertImages[0])
        vertImage1 = image.img_to_array(vertImage1)
        vertImage1 = vertImage1/255.

        vertImage2 = image.load_img(vertPath + '/' + vertImages[0])
        vertImage2 = image.img_to_array(vertImage1)
        vertImage2 = vertImage1/255.

        vertImage3 = image.load_img(vertPath + '/' + vertImages[0])
        vertImage3 = image.img_to_array(vertImage1)
        vertImage3 = vertImage1/255.

        imgLength = vertImage1.shape[0]*vertImage1.shape[1]*vertImage1.shape[2]
        imgShape = vertImage1.shape
        bodyImg = image.load_img(internalPath + '/' + bodyImgPath)
        bodyImg = image.img_to_array(bodyImg)
        bodyImg = bodyImg/255.

        # vertImage1 vertImage2 vertImage3 vert1Pose vert2Pose vert3Pose bodyPose bodyImg
        vImage1.append(vertImage1)
        vImage2.append(vertImage2)
        vImage3.append(vertImage3)
        vPose1.append(vert1Pose)
        vPose2.append(vert2Pose)
        vPose3.append(vert3Pose)
        vPoseB.append(bodyPose)
        vBody.append(bodyImg)

        batch_count += 1

        if batch_count == batch_size:
            vImage1 = np.reshape(vImage1, [batch_size, imgShape[0], imgShape[1], imgShape[2]])
            vImage2 = np.reshape(vImage2, [batch_size, imgShape[0], imgShape[1], imgShape[2]])
            vImage3 = np.reshape(vImage3, [batch_size, imgShape[0], imgShape[1], imgShape[2]])
            vBody = np.reshape(vBody, [batch_size, imgShape[0], imgShape[1], imgShape[2]])

            vPose1 = np.reshape(vPose1, [batch_size, 2])
            vPose2 = np.reshape(vPose2, [batch_size, 2])
            vPose3 = np.reshape(vPose3, [batch_size, 2])
            vPoseB = np.reshape(vPoseB, [batch_size, 2])

            imageConcat = tf.concat([vImage1, vImage2, vImage3], axis=2)
            poseConcat = tf.concat([vPose1, vPose2, vPose3, vPoseB], axis=1)
            print('poseConcat shape: ')
            print(poseConcat.shape)
            time.sleep(20)
            # inputList = [vImage1, vImage2, vImage3, vPose1, vPose2, vPose3, vPoseB]
            inputList = [imageConcat, poseConcat]
            returnTuple = ([inputList, vBody])
            # if releasedVals == 0:
            # print('assigning testVals')
            # print(np.array(vPose1))
            # testVal = [np.array(vImage1), np.array(vImage2), np.array(vImage3), np.array(vPose1), np.array(vPose2), np.array(vPose3), np.array(vPoseB)]
            releasedVals += 1
            print('\nreleasedVals ' + str(releasedVals))
            print('batch_count ' + str(batch_count))
            batch_count = 0
            yield returnTuple
            vImage1 = []
            vImage2 = []
            vImage3 = []
            vBody = []
            vPose1 = []
            vPose2 = []
            vPose3 = []
            vPoseB = []
            inputList = []
            returnTuple = ()
            # batch_count = 0


h = 480
w = 640
channels = 9
midDim = 1000
latentDim = 150
# batch_size=1

#Inputs
# image1 = Input(shape=(h, w, channels))
# image2 = Input(shape=(h, w, channels))
# image3 = Input(shape=(h, w, channels))
# imageCat = Input(batch_shape=(batch_size, h, w, channels))
imageCat = Input(shape=(h, w, channels))

# pose1 = Input(shape=(2,))
# pose2 = Input(shape=(2,))
# pose3 = Input(shape=(2,))
# pose4 = Input(shape=(2,))
# poseCat = Input(batch_shape=(batch_size, 8))
poseCat = Input(shape=(8,))

# encoder_in = imageCat# Input(shape=(h, w, channels))
x = Conv2D(10, (5, 5), padding='same', activation='relu')(imageCat)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(20, (5, 5), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(30, (5, 5), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(35, (5, 5), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2,2))(x)
print(x.shape)
x = Conv2D(40, (5, 5), padding='same', activation='relu')(x)
print(x.shape)
x = MaxPooling2D((2, 2))(x)
# x = Conv2D(40, (5, 5), padding='same', activation='relu')(x)
# print(x.shape)
shape = x.get_shape().as_list()
print('shape')
print(shape[1])
print(shape[2])
print(shape[3])
# time.sleep(20)
x = Flatten()(x)
z = Dense(latentDim, activation='relu')(x)
print('z')
print(z.shape)
print('poseCat')
print(poseCat.shape)


# latent_z = tf.concat([z, poseCat], axis=1)
latent_z = keras.layers.concatenate([poseCat, z])
# latent_z = Lambda(concat_dims, output_shape=(latentDim+8,), name='z1')([poseCat, z])
print('latent z shape')
print(latent_z.shape)


# Now write the decoder
decoder_in = Dense(shape[1]*shape[2]*shape[3], activation='relu')(latent_z)
x = keras.layers.Reshape((shape[1], shape[2], shape[3]))(decoder_in)
print('decoder in shape')
print(x.shape)
x = Conv2D(40, (5, 5), activation='relu', padding='same')(x)
x = UpSampling2D((2, 2))(x) 
print(x.shape)
x = Conv2D(35, (5, 5), padding='same', activation='relu')(x) 
x = UpSampling2D((2, 2))(x) 
print(x.shape)
x = Conv2D(30, (5, 5), padding='same', activation='relu')(x) 
x = UpSampling2D((2, 2))(x) 
print(x.shape)
x = Conv2D(20, (5, 5), padding='same', activation='relu')(x) 
x = UpSampling2D((2, 2))(x) 
print(x.shape)
x = Conv2D(15, (5, 5), padding='same', activation='relu')(x)
x = UpSampling2D((2, 2))(x)
print(x.shape)
x = Conv2D(10, (5,5), padding='same', activation='relu')(x)
#x = Conv2D(5, (5,5), padding='same', activation='relu')(x)
decoder_out = Conv2D(3, (5, 5), activation='sigmoid', padding='same')(x) 
print('decoder out')
print(decoder_out.shape)

ae = Model(inputs=[imageCat, poseCat], outputs=decoder_out)

trainGenerator = my_gen()
ae.compile(loss='mse', optimizer='adam')
ae.summary()
time.sleep(10)
ae.fit_generator(trainGenerator,
                 steps_per_epoch=4,
                 epochs=20000,
                 validation_steps=1,
                 use_multiprocessing=False,
                 max_queue_size=1)

ae.save('ae_1.h5')


dataPath = "/home/carson/libs/keras_tests/"
vImage1 = [] 
vImage2 = [] 
vImage3 = [] 
vBody = []
vPose1 = []
vPose2 = []
vPose3 = []
vPoseB = []
releasedVals = 0


trainSetIter = random.randint(1,(len(os.listdir(dataPath))))

vertPath = dataPath + "train_set_" + str(trainSetIter) + "/vertices"
internalPath = dataPath + "train_set_" + str(trainSetIter) + "/internal_points"

vertImages = []
vert1Pose = []
vert2Pose = []
vert3Pose = []
splitResult = []

for file in os.listdir(vertPath):
    if file.endswith(".mat") or file.endswith(".txt"):
        splitResult = file.split("_")

resultVec = []
for file in os.listdir(vertPath):
    if file.endswith(".mat") or file.endswith(".txt"):
        splitResult = file.split(".")
        resultVec.append(splitResult[0])

individualVec = []
for val in resultVec:
    splitResult = val.split("_")
    individualVec.append(splitResult)

vertImages.append(individualVec[0][0]+".jpg")
vertImages.append(individualVec[1][0]+".jpg")
vertImages.append(individualVec[2][0]+".jpg")

vert1Pose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
vert1Pose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

vert2Pose.append(float(individualVec[1][1] + "." + individualVec[1][2]))
vert2Pose.append(float(individualVec[1][3] + "." + individualVec[1][4]))

vert3Pose.append(float(individualVec[2][1] + "." + individualVec[2][2]))
vert3Pose.append(float(individualVec[2][3] + "." + individualVec[2][4]))

possibleVals = []
bodyPose = []
#Now do this for a random value in the body directory
for file in os.listdir(internalPath):
    if file.endswith(".mat") or file.endswith(".txt"):
        possibleVals.append(file)

#Choose random file
bodyFile = possibleVals[random.randint(0,(len(possibleVals)-1))]

#Now parse it
resultVec = []
splitResult = bodyFile.split(".")
resultVec.append(splitResult[0])

individualVec = []
for val in resultVec:
    splitResult = val.split("_")
    individualVec.append(splitResult)

bodyPose.append(float(individualVec[0][1] + "." + individualVec[0][2]))
bodyPose.append(float(individualVec[0][3] + "." + individualVec[0][4]))

#Now we have bodyPose, bodyImg, vert1Pose, vert2Pose, vert3Pose, vertImages
vertImage1 = image.load_img(vertPath + '/' + vertImages[0])
vertImage1 = image.img_to_array(vertImage1)
vertImage1 = vertImage1/255.

vertImage2 = image.load_img(vertPath + '/' + vertImages[0])
vertImage2 = image.img_to_array(vertImage1)
vertImage2 = vertImage1/255.

vertImage3 = image.load_img(vertPath + '/' + vertImages[0])
vertImage3 = image.img_to_array(vertImage1)
vertImage3 = vertImage1/255.

imgLength = vertImage1.shape[0]*vertImage1.shape[1]*vertImage1.shape[2]
imgShape = vertImage1.shape

vImage1.append(vertImage1)
vImage2.append(vertImage2)
vImage3.append(vertImage3)
vPose1.append(vert1Pose)
vPose2.append(vert2Pose)
vPose3.append(vert3Pose)
vPoseB.append(bodyPose)

vImage1 = np.reshape(vImage1, [1, imgShape[0], imgShape[1], imgShape[2]])
vImage2 = np.reshape(vImage2, [1, imgShape[0], imgShape[1], imgShape[2]])
vImage3 = np.reshape(vImage3, [1, imgShape[0], imgShape[1], imgShape[2]])
# vBody = np.reshape(vBody, [1, imgShape[0], imgShape[1], imgShape[2]])

vPose1 = np.reshape(vPose1, [1, 2])
vPose2 = np.reshape(vPose2, [1, 2])
vPose3 = np.reshape(vPose3, [1, 2])
vPoseB = np.reshape(vPoseB, [1, 2])

testVal = [vImage1, vImage2, vImage3, vPose1, vPose2, vPose3, vPoseB]

bodyImgPath = individualVec[0][0] + ".jpg"
print(bodyImgPath)
bodyImg = image.load_img(internalPath + '/' + bodyImgPath)   
bodyImg = image.img_to_array(bodyImg)
bodyImg = bodyImg/255.

# print(testVal)
newImage = ae.predict(testVal)
newImage = np.reshape(newImage, [imgShape[0], imgShape[1], imgShape[2]])

scipy.misc.imwrite('newImage.jpg', newImage)
# print(newImage.shape)
'''
fig = plt.figure(figsize=(10,4))
fig.add_subplot(1,2,1)
plt.imshow(bodyImg)
fig.add_subplot(1,2,2)
plt.imshow(newImage)
plt.savefig('newImage001.png')
plt.show()
'''
