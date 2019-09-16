import cv2
import numpy as np
import matplotlib.pyplot as plt

data_loc = './dataset/'
imgL = data_loc + 'im0.png'
imgR = data_loc + 'im1.png'

imgL = cv2.resize(cv2.imread(imgL, 0), (400, 400))
imgR = cv2.resize(cv2.imread(imgR, 0), (400, 400))

f = plt.figure()
f.add_subplot(1, 2, 1)
plt.imshow(imgL)
f.add_subplot(1, 2, 2)
plt.imshow(imgR)
plt.show(block=False)
plt.pause(5)

maxdisp = 40

cost = np.zeros((maxdisp, 400, 400))

f = plt.figure()

for i in range(maxdisp // 4):
    if i > 0:
        cost[:i, :, i:] = imgL[:, i:]
        cost[i, :, i:] = imgR[:, :-i]

    else:
        cost[i, :, :] = imgL
        cost[i, :, :] = imgR

    plt.imshow(cost[i, :, :])
    plt.show(block=False)
    plt.pause(1)
