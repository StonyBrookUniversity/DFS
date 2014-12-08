#!/usr/bin/python
import os
import sys
import random
scriptpath = "../fslib/util.py"
sys.path.append(os.path.abspath(scriptpath))
#from fslib.util import *
from util import *
########################################################################################################################
# "" Creating DOT File""
########################################################################################################################
"""
Initial Processing
"""
fi = open("traffic", "r")
fj = open("navid", "r")
trafficmatrix = open('traffic', 'r')
fo = open("traffic_navid.dot", "wb")
sys.stdout=fo

RouterFlowStartDict = dict()
RouterFlowSizeDict = dict()
RouterFlowDurationDict = dict()

RouterDict = dict()

for line in fi:
    if line.strip()!= "":
        Flow=line.strip().split(" ")
        if (Flow!="") and (Flow[1] in RouterFlowStartDict):
            RouterFlowStartDict[Flow[1]].append(float(Flow[0]))
            RouterFlowSizeDict[Flow[1]].append(float(Flow[3]))
        else:
            RouterFlowStartDict[Flow[1]] = []
            RouterFlowSizeDict[Flow[1]] = []
            RouterFlowStartDict[Flow[1]].append(float(Flow[0]))
            RouterFlowSizeDict[Flow[1]].append(float(Flow[3]))

fi.seek(0)
counter = 0
for line in fi:
    if line.strip() != "":
        Flow = line.strip().split(" ")
        if Flow[1] not in RouterDict:
            counter += 1
            RouterDict[Flow[1]]={'autoack': [['False']]}
            RouterDict[Flow[1]]['ipdests'] = [nodename_to_ipaddr(Flow[1])]
            RouterDict[Flow[1]]['traffic'] = [['m']]
            RouterDict[Flow[1]]['m'] = []
            RouterDict[Flow[1]]['m'].append(["modulator "])
            RouterDict[Flow[1]]['m'].append(["start=0.0 "])
            RouterDict[Flow[1]]['m'].append(["generator=s "])
            RouterDict[Flow[1]]['m'].append(["profile=((%s),(1,))"%(str((len(RouterFlowStartDict[Flow[1]])+1))+',')])
            RouterDict[Flow[1]]['s'] = [("matrix flowstart=randomchoice(1) ipproto=randomchoice(6) sport=randomunifint(1025,65535) dport=randomunifint(1025,65535) lossrate=randomchoice(0.001) matrix=conf/input.matrix")]


print "graph test {"
print "flowexport=text"

"""
Node Description And Traffic Generation Code
"""
for k,v in RouterDict.iteritems():  ##Outer Dictionary
    print k,
    RouterProp=v
    print "["
    for k1,v1 in RouterProp.iteritems(): ##Inner Dictionary
        #print k1
        PropertyList=v1 ##List of Router Properties
        PropertyStr=""
        for item in PropertyList: ## item is list list
            PropertyStr+= ''.join(item)
            #PropertyStr+= ' '
        print "\t"+k1+"="+"\""+str(PropertyStr)+"\""
    print"];"

"""
Topology Generation Code
"""
for line in fj:
    if line!= "":
        Link=line.split(" ")
        if Link[0][0]=='S' and Link[1][0]=='S':
            print 'H'+Link[0].strip('S')+ " -- "+'H'+Link[1].strip('S')+"[weight=10, capacity=1000000000, delay=0.001]"
print "}\n"
########################################################################################################################
# "" Creating INPUT File""
########################################################################################################################
""""
Initial Processing
"""
fo = open("input.matrix", "wb")
sys.stdout=fo
flowList = []
matrixList=[]
matrixList.append([])
matrixList.append([])
matrixList.append([])
matrixList.append([])

"""
Input File Generation Code
"""
for line in trafficmatrix:
    if line.strip()!= "":
        flowList.append(line.strip().split(" "))

for item in  flowList:
    matrixList[0].append(item[0])
    matrixList[1].append("10.1.1.%d"%(int(item[1].strip().strip('H'))%254))
    matrixList[2].append("10.1.1.%d"%(int(item[2].strip().strip('H'))%254))
    matrixList[3].append(item[3])

for i in  range(len(matrixList[0])):
    print matrixList[0][i],
    print matrixList[1][i],
    print matrixList[2][i],
    print matrixList[3][i]
