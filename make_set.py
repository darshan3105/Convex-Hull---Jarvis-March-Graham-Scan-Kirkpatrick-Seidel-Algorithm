import csv
import random
import sys

print("Enter the number of data points:")
x = int(input())

with open('datasets/1.csv','w') as csvfile:
    writer = csv.writer(csvfile);
    for i in range(0,x):
        f = random.randrange(-x,x+1,2)
        s = random.randrange(-x,x+1,2)
        row = [f,s]
        writer.writerow(row)

csvfile.close()
