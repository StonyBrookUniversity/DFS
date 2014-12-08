import sys
import re
from subprocess import Popen, PIPE
import os.path
import glob

filename = raw_input("Enter filename: ")
f = open(filename,"r")
Delta=[]

for line in f:
    if line.strip()!= "":
        Delta.append(float(line.strip().split(" ")[0]))

print reduce(lambda x, y: x + y, Delta) / len(Delta)
print max(Delta)
print min(Delta)
