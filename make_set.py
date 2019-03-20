import csv
import random

with open('datasets/1.csv','a') as csvfile:
    writer = csv.writer(csvfile);
    for i in range(0,100):
        f = random.randrange(-100,101,2)
        s = random.randrange(-100,101,2)
        row = [f,s]
        writer.writerow(row)

csvfile.close()
