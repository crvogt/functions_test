import matplotlib.pyplot as plt
import cv2
from matplotlib.transforms import offset_copy

font_size = 22
n_rows = 5
n_cols = 4

img = '/home/carson/Desktop/test.jpg'
# cols = ['Column {}'.format(col) for col in range(1, n_cols+1)]
# rows = ['Row {}'.format(row) for row in ['Ref', 'Ours', 'LIME', 'Gain', 'NPE']]
rows = [row for row in ['ref', 'ours', 'LIME', 'gain', 'NPE']]

# fig, axes = plt.subplots(nrows=n_rows, ncols=n_cols, figsize=(12, 8))
# plt.setp(axes.flat, xticks=[], yticks=[])

fig = plt.figure()
axes = [fig.add_subplot(n_rows, n_cols, r * n_cols + c) for r in range(1, n_rows) for c in range(1, n_cols)]

for ax in axes:
    ax.

# for ax in axes:
#     ax.plot
# pad = 1  # in points

# for ax, col in zip(axes[0], cols):
#     ax.annotate(col, xy=(0.5, 1), xytext=(0, pad),
#                 xycoords='axes fraction', textcoords='offset points',
#                 size='large', ha='center', va='baseline')

# for ax, row in zip(axes[:, 0], rows):
#     ax.annotate(row, xy=(0, 0.5), xytext=(-ax.yaxis.labelpad - pad, 0),
#                 xycoords=ax.yaxis.label, textcoords='offset points',
#                 size='large', ha='right', va='center')

# fig.tight_layout()
# tight_layout doesn't take these labels into account. We'll need
# to make some room. These numbers are are manually tweaked.
# You could automatically calculate them, but it's a pain.
# fig.subplots_adjust(left=0.1, top=0.95)

plt.show()

# import matplotlib.pyplot as plt
#
# cols = ['Column {}'.format(col) for col in range(1, 4)]
# rows = ['Row {}'.format(row) for row in ['A', 'B', 'C', 'D']]
#
# fig, axes = plt.subplots(nrows=4, ncols=3, figsize=(12, 8))
#
# for ax, col in zip(axes[0], cols):
#     ax.set_title(col)
#
# for ax, row in zip(axes[:,0], rows):
#     ax.set_ylabel(row, rotation=0, size='large')
#
# fig.tight_layout()
# plt.show()


# import tkinter as tk
# from PIL import ImageTk, Image
#
# #This creates the main window of an application
# window = tk.Tk()
# window.title("Join")
# window.geometry("300x300")
# window.configure(background='grey')
#
# path = '/home/carson/libs/raytrix_gp_data/raytrixImages/high_light_raw/0.png'
#
# #Creates a Tkinter-compatible photo image, which can be used everywhere Tkinter expects an image object.
# img = ImageTk.PhotoImage(Image.open(path))
#
# #The Label widget is a standard Tkinter widget used to display a text or image on the screen.
# panel = tk.Label(window, image = img)
#
# #The Pack geometry manager packs widgets in rows or columns.
# panel.pack(side = "bottom", fill = "both", expand = "yes")
#
# #Start the GUI
# window.mainloop()


# import matplotlib.pyplot as plt
# import cv2
# import time
# import image
#
#
# image.new(colour_mode, size=(x,y), colour)
# image.paste(img, (left, up, right, down))
#
#
#
# # fig,ax = plt.subplots(2,5)
#
# # filenames=['/home/carson/libs/raytrix_gp_data/raytrixImages/high_light_raw/0.png'.format(i) for i in range(10)] #or glob or any other way to describe filenames
#
# # for i in range(0, 10):
# # 	filenames=['/home/carson/libs/raytrix_gp_data/raytrixImages/high_light_raw/0.png]
#
# # for i in range(0, 10):
# # 	# with open(filenames[i],'rb') as f:
# #     f = '/home/carson/libs/raytrix_gp_data/raytrixImages/high_light_raw/' + str(i) + '.png'
# #     print(f)
# #     image=cv2.imread(f)
# #     ax[i%2][i//2].imshow(image)
# #     # time.sleep(2)
# # fig.show()
# # print('showing')
# # time.sleep(20)