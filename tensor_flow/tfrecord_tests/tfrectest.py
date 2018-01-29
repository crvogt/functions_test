import numpy as np 
import skimage.io as io 
from matplotlib import pyplot as plt
	
ps3_image = io.imread('1000.jpg')
io.imshow(ps3_image)
# plt.show()

# Now convert the picture into string representation
ps3_string = ps3_image.tostring()

# Now convertt back to image 
# Important: dtype should be specified otherwise
# the reconstruction will be errorness?
# reconstruction is 1d, so we need sizes of image
# to fully reconstruct it 
reconstructed_ps3_1d = np.fromstring(ps3_string, dtype=np.uint8)

# Here we reshape the 1d representation
# This is why we need to store the size of image 
# along with its serialized representation
reconstructed_ps3_img = reconstructed_ps3_1d.reshape(ps3_image.shape)

# Chec if we got everything right and compare
# reconstruced array to the original one
if np.allclose(ps3_image, reconstructed_ps3_img):
	print("All good!")

io.imshow(reconstructed_ps3_img)

# Creating a .tfrecord file and reading it without defining
# a graph.

# 3 Images/annotations to .tfreccord file and read without
# defining a computational graph
# We also make sure the read images are equal to the original 
# images 
# We also write the sizes of the images along with the image in
# the raw format.

# Get some image/annotation pairs
filename_pairs = [('32.jpg', '32.png'), ('39.jpg','39.png'),('63.jpg','63.png')]