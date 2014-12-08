#!/usr/bin/python
import os
#from fslib.util import *
import sys
import random
scriptpath1 = "../fslib/util.py"
sys.path.append(os.path.abspath(scriptpath1))
scriptpath2 = ".."
sys.path.append(os.path.abspath(scriptpath2))
from fslib.util import *
from util import *
print "NETWORKSIZE",NETWORKSIZE
print "FSONum", FSONum
print "MirrorNum",MirrorNum

########################################################################################################################
# "" Creating DOT File""
########################################################################################################################
"""
Initial Processing
"""
fi = open("traffic_uniform.txt", "r")
#fi = open("traffic64_05", "r")
trafficmatrix = open('traffic_uniform.txt', 'r')
#trafficmatrix = open('traffic64_05', 'r')
fo = open("traffic_logic.dot", "wb")
foback=sys.stdout
sys.stdout=fo

RouterFlowStartDict = dict()
RouterFlowSizeDict = dict()
RouterFlowDurationDict = dict()

SRouterDict = dict()
DRouterDict = dict()

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
        if Flow[1] not in SRouterDict:
            counter += 1
            SRouterDict[Flow[1]]={'autoack': [['False']]}
            SRouterDict[Flow[1]]['ipdests'] = [nodename_to_ipaddr('H'+str(int( Flow[1][1:])+1))]
            SRouterDict[Flow[1]]['traffic'] = [['m']]
            SRouterDict[Flow[1]]['m'] = []
            SRouterDict[Flow[1]]['m'].append(["modulator "])
            SRouterDict[Flow[1]]['m'].append(["start=0.0 "])
            SRouterDict[Flow[1]]['m'].append(["generator=s "])
            SRouterDict[Flow[1]]['m'].append(["profile=((%s),(1,))"%(str((len(RouterFlowStartDict[Flow[1]])+1))+',')])
            SRouterDict[Flow[1]]['s'] = [("matrix flowstart=randomchoice(1) ipproto=randomchoice(6) sport=randomunifint(1025,65535) dport=randomunifint(1025,65535) lossrate=randomchoice(0.0045) matrix=../conf/input.matrix")]

fi.seek(0)
for line in fi:
    if line.strip() != "":
        Flow = line.strip().split(" ")
        if Flow[2] not in DRouterDict:
            counter += 1
            DRouterDict[Flow[2]]={'autoack': [['False']]}
            DRouterDict[Flow[2]]['ipdests'] = [nodename_to_ipaddr('H'+str(int( Flow[2][1:])+1))]

print "graph test {"
print "flowexport=text"
print "counterexportfile=\"counters\""
print "counterexport=True"
print "counterexportinterval=1"

"""
Node Description And Traffic Generation Code
"""
for k,v in SRouterDict.iteritems():  ##Outer Dictionary
    print 'H'+str(int(k[1:])+1),
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

for k,v in DRouterDict.iteritems():  ##Outer Dictionary
    if k not in SRouterDict.iterkeys():
        print 'H'+str(int(k[1:])+1),
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
#import networkControlLogic2module

#networkControlLogic2object = networkControlLogic2module.networkControlLogic2class()
#networkControlLogic2object.initilize(64,16,8,networkControlLogic2module.oursCongestion)

initTopology=networkControlLogic2object.initTopology
for i in range(0,NETWORKSIZE):
    for j in range(0,i):
        if initTopology[i][j]:
            print "H%d -- H%d[weight=10, capacity=1000000000, delay=0.0005]"%(i+1,j+1)
print "}\n"

initAdditionalTopology=networkControlLogic2object.initAdditionalTopology
for i in range(0,NETWORKSIZE):
    for j in range(0,i):
        if initAdditionalTopology[i][j]:
            print "H%d -- H%d[weight=10, capacity=10000000, delay=0.0005]"%(i+1,j+1)
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
    matrixList[1].append("10.1.1.%d"%(int(item[1].strip().strip('H'))%254+1))
    matrixList[2].append("10.1.1.%d"%(int(item[2].strip().strip('H'))%254+1))
    matrixList[3].append(item[3])

for i in  range(len(matrixList[0])):
    print matrixList[0][i],
    print matrixList[1][i],
    print matrixList[2][i],
    print matrixList[3][i]

sys.stdout=foback

import fs
fs.main()
print "Hi"
