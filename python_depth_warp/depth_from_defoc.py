import numpy as np
import time
import cv2
from scipy.interpolate import RectBivariateSpline


def display_lf(imgArray):
    for iVal in range(1, 16):
        for jVal in range(1, 16):
            cv2.imshow("img", imgArray[:, :, :, jVal-1, iVal-1])
            cv2.waitKey(100)


def interp2(grayImg, moveX, moveY):
    height, width = grayImg.shape
    # print(moveX.size)
    # print(height, width)
    # time.sleep(20)
    x = np.arange(0, width, 1)
    y = np.arange(0, height, 1)

    # print("moveX: " + str(moveX))
    # print("moveY: " + str(moveY))

    interped = RectBivariateSpline(y, x, grayImg)

    x2 = np.linspace(moveX, width + moveX, width)
    y2 = np.linspace(moveY, height + moveY, height)

    Z = interped(y2, x2)
    Z = Z.astype(np.uint8)

    # Going to leave this for now, might have to revisit
    # if moveY <= 0:
    #     Z[0:height, 0:int(moveY)] = 0
    #     Z[0:int(moveX), 0:width] = 0
    # else
    #     Z[0:height, 0:int(moveY)] = 0
    #     Z[0:int(moveX), 0:width] = 0


    # cv2.imshow("sheared lf", Z)
    # cv2.imwrite("shearTests/"+str(moveX)+"_"+str(moveY)+".png", Z)
    # cv2.waitKey(100)

    return Z


nRows = 15
nCols = 15

# Load light field SAIs
lfLocation = "/home/carson/libs/SAI_output/"

LF = np.zeros((101, 101, 3, nRows, nCols), dtype=np.uint8)

terCount = 0
for xTer in range(1, 16):
    for yTer in range(1, 16):
        lfName = ""
        if xTer > 9 and yTer > 9:
            lfName = "CRV_" + str(xTer) + "_" + str(yTer) + ".png"
        elif xTer < 10 and yTer < 10:
            lfName = "CRV_0" + str(xTer) + "_0" + str(yTer) + ".png"
        elif xTer < 10 and yTer > 9:
            lfName = "CRV_0" + str(xTer) + "_" + str(yTer) + ".png"
        else:
            lfName = "CRV_" + str(xTer) + "_0" + str(yTer) + ".png"

        lfName = lfLocation + lfName
        src = cv2.imread(lfName, 1)

        LF[:, :, :, yTer-1, xTer-1] = src

        terCount = terCount + 1

xx = np.linspace(0, 1, nCols)   # Return numbers over evenly spaced interval
yy = np.linspace(0, 1, nRows)

X, Y = np.meshgrid(xx, yy)

# Gives us the coordinates of all of the images
X = np.asarray(X).reshape(-1)
Y = np.asarray(Y).reshape(-1)
# Center image
cxInd = (X.size-1)/2
cyInd = (Y.size-1)/2
cX = X[cxInd]
cY = Y[cyInd]
# Get delta between images and center image
dX = X - cX
dY = Y - cY

grayLF = np.zeros((101, 101, nRows, nCols), dtype=np.uint8)

# Now for depth magiccccc!!!

defocusStack = np.zeros((101, 101, 100))
correspStack = np.zeros((101, 101, 100))
featuresStack = np.zeros((101, 101, 200))

depthResolution = 100.0
deltaDisparity = 21.0
angRes = nRows
delta = np.linspace(-deltaDisparity, deltaDisparity, 100)
depthNum = 0

for curDepth in delta:
    saiInd = 0
    shearedLF = np.zeros((101, 101, nRows * nCols), dtype=np.uint8)
    for iX in range(0, nCols):
        for iY in range(0, nRows):
            grayLF[:, :, iY, iX] = cv2.cvtColor(LF[:, :, :, iY, iX], cv2.COLOR_BGR2GRAY)

            moveX = curDepth * dX
            moveY = curDepth * dY

            shearedLF[:, :, saiInd] = interp2(grayLF[:, :, iY, iX], moveX[saiInd], moveY[saiInd])

            if iY == 0 and iX == 0:
                print("showing lf: " + str(depthNum))
                cv2.imshow("sheared lf", shearedLF[:, :, saiInd])
                print("Larger version")
                bigImg = cv2.resize(shearedLF[:, :, saiInd], (2*101, 2*101))
                cv2.imshow("bigImg", bigImg)
                # cv2.imwrite("shearTests/"+str(moveX)+"_"+str(moveY)+".png", shearedLF[:, :, saiInd])
                cv2.imwrite("shearTests/" +str(depthNum)+".png", shearedLF[:, :, saiInd])
                cv2.waitKey(200)

            saiInd = saiInd + 1

    depthNum = depthNum + 1




