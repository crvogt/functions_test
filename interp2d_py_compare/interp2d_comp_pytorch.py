import numpy as np
import cv2
from scipy.interpolate import RectBivariateSpline
import torch
import torchvision
import matplotlib.pyplot as plt
import kornia

shift_dist_x = 2
shift_dist_y = 2
# fileName = "40.jpg"
fileName = "lens.png"


src = cv2.imread(fileName, 0)
to_tensor = torchvision.transforms.ToTensor()
img_pt = to_tensor(src)
# img_pt = torch.unsqueeze(img_pt.float(), dim=0)
# img = kornia.image_to_tensor(src)
# img = torch.unsqueeze(img.float(), dim=0)
# img_pt *= 255.

# points_src = torch.FloatTensor([[[0, 0], [480, 0], [0, 640], [480, 640]]])
# points_dst = torch.FloatTensor([[[10, 10], [490, 10], [10, 650], [490, 650]]])

# M = kornia.get_perspective_transform(points_src, points_dst)
# print(M)
M = torch.FloatTensor([[[1., 0., shift_dist_x],
                    [0., 1., shift_dist_y],
                    [0., 0., 1.]]])
print(M)
img = img_pt.view(1, *img_pt.shape)
img_warp = kornia.warp_perspective(img, M, dsize=(24, 24))
print(img_warp.shape)
img_warp = img_warp.squeeze()
img_warp = kornia.tensor_to_image(img_warp)

plt.figure()
img_pt = img_pt.squeeze()
plt.imshow(img_pt+1)

plt.figure()
plt.imshow(img_warp)

# height, width, channels = src.shape
# grayImg = cv2.cvtColor(src, cv2.COLOR_RGB2GRAY)
#
# x = np.arange(0, width, 1)
# y = np.arange(0, height, 1)
#
# interped = RectBivariateSpline(y, x, grayImg)
#
# x2 = np.arange(-shift_dist, width - shift_dist, 1)
# y2 = np.arange(-shift_dist, height - shift_dist, 1)
#
# Z = interped(y2, x2)
# Z = Z.astype(np.uint8)
#
# # # Z[rows,cols]
# Z[0:height, 0:shift_dist] = 0
# Z[0:shift_dist, 0:width] = 0
#
# plt.figure()
# plt.imshow(Z)

plt.show()
