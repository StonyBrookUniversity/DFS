import sys
import re
from subprocess import Popen, PIPE
import os.path
import glob

f = open("Hsum64.txt","wb")
#sys.stdout=f
i=1

for i in range(2,65):#router +1
    FlowCalcList=[]
    FlowCalcList.append([])
    FlowCalcList.append([])
    FlowCalcList.append([])
    fi = open("H%d_flow.txt"%(i),"r")
    for line in fi:
        if line.strip()!= "":
            Flow=line.strip().split(" ")
            if Flow[8][:6]=='matrix':
                FlowCalcList[0].append(Flow[5])
                FlowCalcList[1].append(Flow[3])
                #print FlowCalcList


    for Flowkey in FlowCalcList[0]:
        for j in range(1,65):
            fj = open("H%d_flow.txt"%(j),"r")
            for line in fj:
                if line.strip()!= "":
                    Flow=line.strip().split(" ")
                    if Flowkey==Flow[5] and ((Flow[5].split("->")[1]).split(":")[0]).split(".")[3]==Flow[1].strip("H") :
                        FlowCalcList[2].append(Flow[2])
                        #print FlowCalcList[2]

    for a,b in  zip(FlowCalcList[2],FlowCalcList[1]):
        print float(a)-float(b)
