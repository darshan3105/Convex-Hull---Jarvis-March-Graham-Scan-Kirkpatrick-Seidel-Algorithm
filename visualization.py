import numpy as np
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import matplotlib.animation as animation
import csv
import time

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
            plt.pause(0.1)
            line.pop(0).remove()


        plt.plot(x_hull[i:i+2],y_hull[i:i+2],linewidth = 2,color = 'green',alpha = 0.4)

    #plt.savefig('fig/z.png')
    plt.show()
elif type == 'g':
    lines = []
    i=2
    j=2
    lines.append(plt.plot(x_hull[0:2],y_hull[0:2],linewidth = 2,color = 'green',alpha = 0.4))
    plt.pause(0.1)
    while i < len(x_hull) -1:
        if x_hull[i] == x_scatter[j] and y_hull[i] == y_scatter[j]:
            lines.append(plt.plot(x_scatter[j-1:j+1],y_scatter[j-1:j+1],linewidth = 2,color = 'green',alpha = 0.4))
            # plt.pause(1)
            # k = j - 1
            # while x_scatter[k] != x_hull[i-1] or y_scatter[k] != y_hull[i-1]:
            #     line = lines.pop()
            #     line[0].remove()
            #     plt.pause(0.1)
            #     k-=1
            #
            # line = lines.pop()
            # line[0].remove()
            # lines.append(plt.plot(x_hull[i-1:i+1],y_hull[i-1:i+1],linewidth = 2,color = 'green',alpha = 0.4))
            # plt.pause(0.1)
            i+=1
            j+=1

        else:
            lines.append(plt.plot(x_scatter[j-1:j+1],y_scatter[j-1:j+1],linewidth = 2,color = 'green',alpha = 0.4))
            plt.pause(0.1)
            line = lines.pop()
            line[0].remove()
            plt.pause(0.1)
            while x_hull[i]!=x_scatter[j] or y_hull[i]!=y_scatter[j]:
                j+=1
            j+=1

    l = len(x_hull) - 2
    plt.plot(x_hull[l:l+2],y_hull[l:l+2],linewidth = 2,color = 'green',alpha = 0.4)
    plt.show()
