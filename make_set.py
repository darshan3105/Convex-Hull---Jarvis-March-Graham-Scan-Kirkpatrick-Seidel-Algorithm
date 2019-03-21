import csv
import random

with open('datasets/1.csv','w') as csvfile:
    writer = csv.writer(csvfile);
    for i in range(0,20):
        f = random.randrange(-500,501,2)
        s = random.randrange(-500,501,2)
        row = [f,s]
        writer.writerow(row)

csvfile.close()
