#!/usr/bin/python
import sys
import random
fi = open("traffic_matrix_hotspot", "r")
fj = open("navid_16_16_0_64_d1", "r")
fo = open("hotspot_navid_16_16_0_64_d1.dot", "wb")
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

for k,v in RouterFlowStartDict.iteritems():
    v.insert(0,0)

for k,v in RouterFlowStartDict.iteritems():
        i=1
        while i <  len(v):
            if k in RouterFlowDurationDict:
                RouterFlowDurationDict[k].append(v[i]-v[i-1])
            else:
                RouterFlowDurationDict[k]=[]
                RouterFlowDurationDict[k].append(v[i]-v[i - 1])
            i=i+1

fi.seek(0)
counter = 0
for line in fi:
    if line.strip() != "":
        Flow = line.strip().split(" ")
        if Flow[1] not in RouterDict:
            counter += 1
            RouterDict[Flow[1]]={'autoack': [['False']]}
            RouterDict[Flow[1]]['ipdests'] = ["%d.%d.0.0/16"%((counter/40000)%200+1,(counter/200)%200+1)]
            RouterDict[Flow[1]]['traffic'] = [['m']]
            RouterDict[Flow[1]]['m'] = []
            RouterDict[Flow[1]]['m'].append(["modulator "])
            RouterDict[Flow[1]]['m'].append(["start=0.0 "])
            RouterDict[Flow[1]]['m'].append(["generator=s "])
            RouterDict[Flow[1]]['m'].append(["profile=((%s),(%s))"%(str(RouterFlowDurationDict[Flow[1]]).strip('[').strip(']').replace(" ",""),str(RouterFlowSizeDict[Flow[1]]).strip('[').strip(']').replace(" ",""))])
            RouterDict[Flow[1]]['s'] = [("harpoon ipsrc=%d.%d.%d.0/24 ipdst=%d.%d.%d.0/24 flowsize=pareto(100000,1.2) flowstart=exponential(.5) ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) lossrate=randomchoice(0.0001)"%((counter/40000)%200+1,(counter/200)%200+1,counter%200+1,(counter/40000)%200+1,(counter/200)%200+1,counter%200+6))]

print "graph test {"
print "flowexport=text"
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

for line in fj:
    if line!= "":
        Link=line.split(" ")
        if Link[0][0]=='S' and Link[1][0]=='S':
            print 'H'+Link[0].strip('S')+ " -- "+'H'+Link[1].strip('S')+"[weight ="+str(random.randint(1,10))+", capacity ="+str(100000000)+",delay=0.00001"+"]"
print "}\n"

"""
H29 [
	m1="modulator start=0.0 generator=s1 profile=((10,),(1,)) "
	s1="harpoon ipsrc=10.32.0.0/16 ipdst=10.37.0.0/16 flowsize=pareto(10000,1.2) flowstart=exponential(100.0) ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) lossrate=randomchoice(0.001) "
	traffic="m1  "
	ipdests=""
	autoack="False "
];
"""
