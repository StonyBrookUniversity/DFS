#!/usr/bin/python
import re
fi = open("traffic_matrix_001", "r")
fo = open("traffic_matrix_001.dot", "wb")
fo.write("graph test {\n")
fo.write("\nflowexport=text\n")
RouterDict = dict()
RouterProp = dict()

for line in fi:
    if line!= "":
        counter=0
        LinkList =line.split(" ")
        if LinkList[1] in RouterDict:
            RouterDict[LinkList[1]].append('traffic="m%d"'%counter)
            RouterDict[LinkList[1]].append('m%d="modulator start=0.0 generator=s%counter profile=((3600,),(1,))"'%(counter,counter))
            RouterDict[LinkList[1]].append(' s1 = "harpoon ipsrc=10.$d.0.0/16 ipdst=10.3.1.0/24 flowsize=pareto(10000,1.2) flowstart=exponential(100.0) ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) lossrate=randomchoice(0.001)"')
        else:
            RouterDict[LinkList[1]].append('autoack = "False"')
            RouterDict[LinkList[1]] = ['traffic="m1"']



        if LinkList[1] in RouterDict:
            RouterDict[LinkList[1]][ipdests].append = "10.1.0.0/16"
        else:
            RouterDict[LinkList[1]] = [RouterProp]

        if LinkList[2] in RouterDict:
            RouterDict[LinkList[2]].append('ipdests="10.1.%d.0/16"'%counter)
        else:
            RouterDict[LinkList[2]] = ['ipdests="10.1.%d.0/16"'%counter]
