import cv2
import PIL.Image as image
import numpy as np

tiff_base = '/home/carson/libs/store_imgs/tiff_tests/'
tiff_file = tiff_base + '1680_DepthRay.tiff'
src_to_warp_file = tiff_base + '1680_Raw.png'
src_to_warp_gray_file = tiff_base + '1680_Gray.png'
src_target_file = tiff_base + '1679_Raw.png'

img = image.open(tiff_file)

imArray = np.asarray(img)

src = cv2.imread(src_to_warp_file, 0)
gray = cv2.imread(src_to_warp_gray_file, 0)

width = 2048/2
start = width / 2

src = src[start:start+width, start:start+width]
gray = gray[start:start+width, start:start+width]

cv2.imwrite(tiff_base+'test_gray.png', gray)
cv2.imwrite(tiff_base+'test_raw.png', src)