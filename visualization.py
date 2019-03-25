import numpy as np
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import matplotlib.animation as animation
import csv
import time

def orientation(p1,p2,p3):

    val = (p2[1] - p1[1])*(p3[0] - p2[0]) - (p2[0] - p1[0])*(p3[1] - p2[1])
    if val == 0:
        return 0
    elif val > 0:
        return 1
    else:
        return 2

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
x_scatter = np.asarray(x_scatter)
y_scatter = np.asarray(y_scatter)
x_hull = np.asarray(x_hull)
y_hull = np.asarray(y_hull)

plt.close('all')
plt.scatter(x_scatter,y_scatter,s = 20)

print("Enter hull type:")
type = input()

if type == 'j':
    for i in range(0,len(x_hull) -1):
        for j in range(0,len(x_scatter)):

            x_temp = []
            y_temp = []
            x_temp.append(x_hull[i])
            y_temp.append(y_hull[i])
            x_temp.append(x_scatter[j])
            y_temp.append(y_scatter[j])


            line = plt.plot(x_temp,y_temp,linewidth = 2,color = 'red',alpha = 0.4)
            #plt.savefig('fig/foo'+str(i)+'_'+str(j)+'.png')
            plt.pause(0.05)
            line.pop(0).remove()


        plt.plot(x_hull[i:i+2],y_hull[i:i+2],linewidth = 2,color = 'green',alpha = 0.4)

    #plt.savefig('fig/z.png')
    plt.show()
elif type == 'g':
    points = []
    lines = []
    lines.append(plt.plot(x_scatter[0:2],y_scatter[0:2],linewidth = 2,color = 'green',alpha = 0.4))
    plt.pause(0.05)
    lines.append(plt.plot(x_scatter[1:3],y_scatter[1:3],linewidth = 2,color = 'green',alpha = 0.4))
    plt.pause(0.05)
    points.append((x_scatter[0],y_scatter[0]))
    points.append((x_scatter[1],y_scatter[1]))
    points.append((x_scatter[2],y_scatter[2]))

    for i in range(3,len(x_scatter)):
        top = points[len(points)-1]
        next_to_top = points[len(points)-2]
        while orientation(next_to_top,top,(x_scatter[i],y_scatter[i])) != 2:
            x_temp = []
            y_temp = []
            x_temp.append(x_scatter[i])
            x_temp.append(top[0])
            y_temp.append(y_scatter[i])
            y_temp.append(top[1])
            lines.append(plt.plot(x_temp,y_temp,linewidth = 2,color = 'green',alpha = 0.4))
            plt.pause(0.05)

            line = lines.pop()
            line[0].remove()
            plt.pause(0.05)

            points.pop()

            line = lines.pop()
            line[0].remove()
            plt.pause(0.05)

            top = points[len(points)-1]
            next_to_top = points[len(points)-2]

        points.append((x_scatter[i],y_scatter[i]))
        x_temp = []
        y_temp = []
        x_temp.append(points[len(points)-1][0])
        x_temp.append(points[len(points)-2][0])
        y_temp.append(points[len(points)-1][1])
        y_temp.append(points[len(points)-2][1])
        lines.append(plt.plot(x_temp,y_temp,linewidth = 2,color = 'green',alpha = 0.4))
        plt.pause(0.05)

    l = len(x_hull) - 2;
    x_temp = []
    y_temp = []
    x_temp.append(x_hull[l])
    x_temp.append(x_hull[l+1])
    y_temp.append(y_hull[l])
    y_temp.append(y_hull[l+1])
    lines.append(plt.plot(x_temp,y_temp,linewidth = 2,color = 'green',alpha = 0.4))

    plt.show()
