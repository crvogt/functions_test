import cv2
import os
import numpy as np
import params
import time
from scipy.interpolate import RectBivariateSpline
from keras.layers import Conv2DTranspose, concatenate
from keras.models import load_model
from keras.preprocessing import image
import keras.backend as K
import matplotlib.pyplot as plt


def display_lf(LF):
    for iVal in range(1, 16):
        for jVal in range(1, 16):
            cv2.imshow("img", LF[:, :, :, jVal-1, iVal-1])
            cv2.waitKey(100)

def h5_sais(LF, h5File, dCounter, light):
    print("Saving light field SAIs to h5...")
    imgList = []
    for iVal in range(1, 16):
        for jVal in range(1, 16):
            img = LF[0:100, 0:100, :, jVal-1, iVal-1]
            img = image.img_to_array(img)
            img = img/255.
            # imgShape = img.shape
            # img = np.reshape(img, [1, imgShape[0], imgShape[1], imgShape[2]])
            # img = np.reshape(img, [imgShape[0], imgShape[1], imgShape[2]])
            imgList.append(img)

    h5File.create_dataset("dataset_"+str(light)+"_"+str(dCounter), data=imgList)


def interp2(grayImg, moveX, moveY):
    height, width = grayImg.shape

    x = np.arange(0, width, 1)
    y = np.arange(0, height, 1)

    interped = RectBivariateSpline(y, x, grayImg, kx=1, ky=1)

    x2 = np.linspace(moveX, width + moveX, width)
    y2 = np.linspace(moveY, height + moveY, height)

    Z = interped(y2, x2)
    Z = Z.astype(np.uint8)

    return Z


def interp2WithMap(depth_map, img2D, delX, delY):
    # Going to need to do this PER channel
    img2DShape = img2D.get_shape().as_list()
    # print(depth_map.shape)
    # time.sleep(20)
    # Am I going to need batch numbers??
    # batch = K.shape(img2D)[0]
    # height = K.shape(img2D)[1]
    # width = K.shape(img2D)[2]
    # channels = K.shape(img2D)[3]
    batch = img2DShape[0]
    height = img2DShape[1]
    width = img2DShape[2]
    channels = img2DShape[3]
    # print(width)
    # time.sleep(20)
    x = np.arange(0, width, 1)
    # x_dim = x.shape
    y = np.arange(0, height, 1)
    # for channels in img2D
    Z = np.zeros(img2DShape[1:4])
    # print(Z.shape)

    for it in range(1, channels):
        # print(img2D[:, :, it].get_shape())
        Z = img2D[:, :, it]
        print(Z.shape)
        x = x.reshape(batch, x_dim)
        print(x.shape)
        time.sleep(20)
        interped = RectBivariateSpline(y, x, img2D[:, :, it], kx=1, ky=1)
        numElem = depth_map.shape[1]*depth_map.shape[2]
        depth_map = np.reshape(depth_map, (1, numElem))
        x2 = x + delX * depth_map
        y2 = y + delY * depth_map
        tmp = interped(y2, x2)
        print('tmp shape')
        print(tmp.shape)
        Z[:, :, it] = tmp#interped(y2, x2)
        Z[:, :, it] = Z[:, :, it].astype(np.uint8)

    return Z


def DefocusResp(input):
    curMean = np.nanmean(input, axis=2)
    np.nan_to_num(curMean, copy=False)
    return curMean


def CorrespResp(input):
    curVar = np.nanvar(input, axis=2)
    np.nan_to_num(curVar, copy=False)
    return curVar


def LoadLF(lfLocation):
    print("Loading light field...")
    LF = np.zeros((params.saiHEIGHT, params.saiWIDTH, params.saiCHANNELS, params.angRes, params.angRes), dtype=np.uint8)
    terCount = 0
    for xTer in range(1, 16):
        for yTer in range(1, 16):
            lfName = ""
            if xTer > 9 and yTer > 9:
                lfName = "/CRV_" + str(xTer) + "_" + str(yTer) + ".png"
            elif xTer < 10 and yTer < 10:
                lfName = "/CRV_0" + str(xTer) + "_0" + str(yTer) + ".png"
            elif xTer < 10 and yTer > 9:
                lfName = "/CRV_0" + str(xTer) + "_" + str(yTer) + ".png"
            else:
                lfName = "/CRV_" + str(xTer) + "_0" + str(yTer) + ".png"

            lfName = lfLocation + lfName
            # print(lfName)
            # src = cv2.imread(lfName, 1)
            # Using keras preprocess
            src = image.load_img(lfName)
            LF[:, :, :, yTer - 1, xTer - 1] = src

            terCount = terCount + 1

    return LF

def SaveLF(LFImg, lfLocation, xTer, yTer):
    lfName = ""
    if xTer > 9 and yTer > 9:
        lfName = "/CRV_" + str(xTer) + "_" + str(yTer) + ".png"
    elif xTer < 10 and yTer < 10:
        lfName = "/CRV_0" + str(xTer) + "_0" + str(yTer) + ".png"
    elif xTer < 10 and yTer > 9:
        lfName = "/CRV_0" + str(xTer) + "_" + str(yTer) + ".png"
    else:
        lfName = "/CRV_" + str(xTer) + "_0" + str(yTer) + ".png"

    lfName = lfLocation + lfName

    image.save_img(lfName, LFImg)


def upsample_and_concat(l1, l2, outChan, inChan):
    convT = Conv2DTranspose(inChan, (3, 3), strides=(2, 2), padding='same', activation='relu')(l1)
    convT = concatenate([convT, l2])
    return convT


def displayResult():
    modelFile = params.modelLocation
    model = load_model(modelFile)
    # darkImgLoca = "/home/carson/libs/SAI_output/scene_1/dark/CRV_08_08.png"
    darkImgLoca = "/home/carson/libs/raytrix_data/light_test_1/l1/g0/l1g0sai/CRV_08_08.png"
    lightImgLoca = "/home/carson/libs/SAI_output/scene_1/light/CRV_08_08.png"
    # darkImgLoca = "/home/carson/libs/raytrix_gp_data/raytrixImages/low_light/17/CRV_01_01.png"
    # lightImgLoca = "/home/carson/libs/raytrix_gp_data/raytrixImages/high_light/17/CRV_01_01.png"
    x_img = image.load_img(darkImgLoca)
    x_img = image.img_to_array(x_img)
    x_img = x_img / 255.
    imgShape = x_img.shape
    x_img = np.reshape(x_img, [1, imgShape[0], imgShape[1], imgShape[2]])

    print("showing new image...")

    newImg = model.predict(x_img)
    newImg = np.reshape(newImg, [imgShape[0], imgShape[1], imgShape[2]])

    darkImg = image.load_img(darkImgLoca)
    darkImg = image.img_to_array(darkImg)
    darkImg = darkImg/255.

    lightImg = image.load_img(lightImgLoca)
    lightImg = image.img_to_array(lightImg)
    lightImg = lightImg/255.

    fig = plt.figure(figsize=(10, 4))
    fig.add_subplot(1, 3, 1)
    plt.imshow(darkImg)
    fig.add_subplot(1, 3, 2)
    plt.imshow(newImg)
    fig.add_subplot(1, 3, 3)
    plt.imshow(lightImg)
    plt.savefig('result001.png')
    plt.show()
