import numpy as np
import time
import cv2

nRows = 15
nCols = 15

xx = np.linspace(0, 1, nCols) # Return numbers over evenly spaced interval
yy = np.linspace(0, 1, nRows)

X, Y = np.meshgrid(xx, yy)

X = np.asarray(X).reshape(-1)
Y = np.asarray(Y).reshape(-1)
# X.reshape()
# print(X.size)
# print(X)
# print(Y[0])

# Load light field SAIs
lfLocation = "/home/carson/libs/SAI_output/"
imgArr = []

terCount = 0

for iTer in range(1,16):
    for jTer in range(1,16):
        lfName = ""
        if iTer > 9 and jTer > 9:
            lfName = "CRV_" + str(iTer) + "_" + str(jTer) + ".png"
        elif iTer < 10 and jTer < 10:
            lfName = "CRV_0" + str(iTer) + "_0" + str(jTer) + ".png"
        elif iTer < 10 and jTer > 9:
            lfName = "CRV_0" + str(iTer) + "_" + str(jTer) + ".png"
        else:
            lfName = "CRV_" + str(iTer) + "_0" + str(jTer) + ".png"

        lfName = lfLocation + lfName
        src = cv2.imread(lfName,1)
        if iTer == 1 and jTer == 1:
            imgArr = src
        else:
            imgArr = np.concatenate((imgArr, src), axis=2)

        # print(str(X[terCount]) + " " + str(Y[terCount]))
        # print(str(terCount) + " " + str(terCount) + "\n")
        # cv2.imshow("src", src)
        # cv2.waitKey(200)
        terCount = terCount + 1
    # iTerCount = iTerCount + 1

print(imgArr.shape)
