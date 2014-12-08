import sys
import re
from subprocess import Popen, PIPE
import os.path
import glob

totalflowsum=0

fi = open("Hflowsum.txt","r")
for line in fi:
    if line.strip()!= "":
        Flow=line.strip().split(" ")
        totalflowsum=totalflowsum+int(Flow[0])
print totalflowsum

