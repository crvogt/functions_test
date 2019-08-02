import os
import matplotlib.pyplot as plt
import numpy as np

# settings
h, w = 10, 10           # for raster image
nrows, ncols = 5, 4     # array of sub plots
figsize = [6, 8]        # figure size, inches

# prep (x,y) for extra plotting on selected sub-plots
xs = np.linspace(0, 2*np.pi, 60)
yx = np.abs(np.sin(xs))

# create a figure (fig), and array of axes(ax)
fig, ax = plt.subplots(nrows=nrows, ncols=ncols, figsize=figsize)

# plot simple raster image on each sub-plot
for i, axi in enumerate(ax.flat)