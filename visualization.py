import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import csv

x_scatter = []
y_scatter = []

with open("datasets/1.csv") as csvfile:
    readcsv = csv.reader(csvfile,delimiter = ',')
    for row in readcsv:
        x_scatter.append(int(row[0]))
        y_scatter.append(int(row[1]))

x_hull = []
y_hull = []

with open("results/results_1.csv") as csvfile:
    readcsv = csv.reader(csvfile,delimiter = ',')
    for row in readcsv:
        x_hull.append(int(row[0]))
        y_hull.append(int(row[1]))

x_hull.append(x_hull[0])
y_hull.append(y_hull[0])


plt.scatter(x_scatter,y_scatter)
plt.plot(x_hull,y_hull,linewidth = 2)
#
plt.show()
