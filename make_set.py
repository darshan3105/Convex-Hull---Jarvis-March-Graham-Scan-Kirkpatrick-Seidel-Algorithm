import csv
import random
import sys

print("Enter the number of data points:")
x = int(input())
y = x//2
with open('datasets/points.csv','w') as csvfile:
    writer = csv.writer(csvfile);
    for i in range(0,x):
        f = random.randrange(-y,y+1,2)
        s = random.randrange(-y,y+1,2)
        row = [f,s]
        writer.writerow(row)

csvfile.close()
