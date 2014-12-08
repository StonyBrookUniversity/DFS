import sys
import re
from subprocess import Popen, PIPE
import os.path
import glob
import numpy as np
#a = [154, 400, 1124, 82, 94, 108]
a = []
#print np.percentile(a,95)

totalflowsum=0

fi = open("Hsum64.txt","r")
for line in fi:
    if line.strip()!= "":
        Flow=line.strip().split(" ")
        a.append(int(Flow[0]))
#print totalflowsum
print np.percentile(a,10), np.percentile(a,25), np.percentile(a,50), np.percentile(a,75), np.percentile(a,90)
