import numpy as np
import cv2
from scipy.interpolate import RectBivariateSpline
import torch
import torchvision

shift_dist = 20
fileName = "40.jpg"

img = cv2.imread(fileName,1)
grayImg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

height, width, channels = img.shape

x = np.arange(0, width, 1)
y = np.arange(0, height, 1)

interped = RectBivariateSpline(y,x,grayImg)

x2 = np.arange(-shift_dist, width - shift_dist, 1)
y2 = np.arange(-shift_dist, height - shift_dist, 1)

Z = interped(y2,x2)
Z = Z.astype(np.uint8)

# Z[rows,cols]
Z[0:height, 0:shift_dist] = 0
Z[0:shift_dist, 0:width] = 0

cv2.imshow("cropping", Z)

cv2.imwrite("pytorch_version.jpg", Z)
cv2.waitKey(5000)