import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import seaborn as sns

x = [0,3,0,0]
y = [0,1,3,0]

x_scatter = [0,3,4,0,0,1,2,3,1]
y_scatter = [0,1,4,3,0,1,2,3,2]

plt.scatter(x_scatter,y_scatter)
plt.plot(x,y,linewidth = 2)

plt.show()
