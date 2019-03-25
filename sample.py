import numpy as np
import matplotlib.pyplot as py
from matplotlib import animation

py.close('all') # close all previous plots

# create a random line to plot
#------------------------------------------------------------------------------

x = np.random.rand(10)
y = np.random.rand(10)

#
# py.figure(1)
# py.scatter(x, y)
# py.axis([0, 1, 0, 1])
# py.show()

# animation of a scatter plot using x, y from above
#------------------------------------------------------------------------------

fig = py.figure(2)
ax = py.axes(xlim=(0, 1), ylim=(0, 1))
scat = ax.scatter(x, y, s=10)

def init():
    scat.set_offsets([])
    return scat

def animate(i):
    # data = np.hstack((x[:i,np.newaxis], y[:i, np.newaxis]))
    # scat.set_offsets(data)
    print(x[i:i+2]," ",y[i:i+2])
    py.plot(x[i:i+2],y[i:i+2],linewidth = 2,color = 'blue')


anim = animation.FuncAnimation(fig, animate, init_func=None, frames=len(x) - 1,
                               interval=200, blit=False, repeat=False)
py.show()
