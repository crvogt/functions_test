import matplotlib.pyplot as plt
import numpy as np

ncols = 5
nrows = 3

# create the plots
fig = plt.figure()
axes = [ fig.add_subplot(nrows, ncols, r * ncols + c) for r in range(0, nrows) for c in range(0, ncols) ]

# add some data
for ax in axes:
    ax.plot(np.random.random(10), np.random.random(10), '.')

# remove the x and y ticks
for ax in axes:
    ax.set_xticks([])
    ax.set_yticks([])
