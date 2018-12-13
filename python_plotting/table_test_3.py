import matplotlib.pyplot as plt
import cv2

read_loc = '/home/carson/libs/store_imgs/demosaic_out/1'

fig = plt.figure(figsize=(10, 4))
src_loc = read_loc + '/dark.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 1)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)

src_loc = read_loc + '/gain.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 2)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)

src_loc = read_loc + '/hist.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 3)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)

src_loc = read_loc + '/npe.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 4)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)

src_loc = read_loc + '/ref.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 5)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)

src_loc = read_loc + '/enh.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 6)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)

src_loc = read_loc + '/srie.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 7)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)

src_loc = read_loc + '/lime.png'
src = plt.imread(src_loc)
fig.add_subplot(2, 4, 8)
plt.imshow(src)

ax = plt.gca()
ax.get_yaxis().set_visible(False)
ax.get_xaxis().set_visible(False)
ax.annotate('Row')

plt.savefig(read_loc + '/figure_denoise.png')
plt.show()