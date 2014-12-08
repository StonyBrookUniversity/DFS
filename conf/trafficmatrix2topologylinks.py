#!/usr/bin/python
import sys
import random

fi = open("008_trafficmatrix", "r")
fj = open("008_topologylinks", "wb")
sys.stdout=fj

for line in fi:
    if line != "":
        Line = line.split(" ")
        print Line[1]+" "+Line[2]+" "+str(random.randint(1,10))+" "+str(random.randint(1000000,100000000))+" "+str(random.randint(0,1))
