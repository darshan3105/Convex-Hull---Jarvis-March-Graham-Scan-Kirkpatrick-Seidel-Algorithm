# import matplotlib.pyplot as plt
# from matplotlib.lines import Line2D
import csv

x_scatter = []
y_scatter = []

with open("datasets/1.csv") as csvfile:
    readcsv = csv.reader(csvfile,delimiter = ',')
    for row in readcsv:
        x_scatter.append(row[0])
        y_scatter.append(row[1])

x_hull = []
y_hull = []

with open("results/results_1.csv") as csvfile:
    readcsv = csv.reader(csvfile,delimiter = ',')
    for row in readcsv:
        x_hull.append(row[0])
        y_hull.append(row[1])

print(x_hull)
print(y_hull)

# plt.scatter(x_scatter,y_scatter)
# plt.plot(x,y,linewidth = 2)
#
# plt.show()
