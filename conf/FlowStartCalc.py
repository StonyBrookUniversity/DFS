import sys
import re
from subprocess import Popen, PIPE
import os.path
import glob

f = open("Hflowstart.txt","wb")
sys.stdout=f
i=1

for i in range(1,65):#router +1
    FlowCalcList=[]
    FlowCalcList.append([])
    FlowCalcList.append([])
    FlowCalcList.append([])
    flowstartsum=0
    fi = open("H%d_flow.txt"%(i),"r")
    for line in fi:
        if line.strip()!= "":
            Flow=line.strip().split(" ")
            #print Flow[3]
            flowstartsum=flowstartsum+float(Flow[3])
    print flowstartsum

"""
    for Flowkey in FlowCalcList[0]:
        for j in range(1,65):
            fj = open("H%d_flow.txt"%(j),"r")
            for line in fj:
                if line.strip()!= "":
                    Flow=line.strip().split(" ")
                    if Flowkey==Flow[5] and ((Flow[5].split("->")[1]).split(":")[0]).split(".")[3]==Flow[1].strip("H") :
                        FlowCalcList[2].append(Flow[2])

    for a,b in  zip(FlowCalcList[2],FlowCalcList[1]):
        print float(a)-float(b)"""
