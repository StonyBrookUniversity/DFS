#!/usr/bin/python
import sys
fi = open("006_trafficmatrix", "r")
fj = open("006_topologylinks", "r")
fo = open("006_topology.dot", "wb")
sys.stdout=fo
print "graph test {"
print "flowexport=text"

SRouterDict = dict()
DRouterDict = dict()
RouterDict = dict()
"""
Dictionaries
S     D     R
SR1   DR1   SR1
SR2   DR2   SR2
			DR1
			DR2
Adding source-router
Case 1: If source-router exists in S (and R): Add new source in R. copy to S. update D if there.
Case 2: if source-router exists in R and not in S(ie it was dest-router): Add source in R. copy it to S and D.
Case 3: if source-router NOT exists in R : Add router in S. copy to R.
Adding dest-router
Case 1: If dest-router exists in D (and R): Add new ipdest in R. copy to D. update S if there.
Case 2: if dest-router exists in R and not in D(ie it was source-router) Add ipdest in R. copy it to D
Case 3: if dest-router NOT exists in R : Add router in D. copy to R.
"""

counter = 0
for line in fi:
    if line!= "":
        counter += 1
        Flow=line.split(" ")
######################################################################################################################
        if Flow[1] in RouterDict:
            if Flow[1] in SRouterDict: ##Case 1: If source-router exists in S (and R): Add new source
                ###
                numSource=0
                for k3 in RouterDict[Flow[1]].iterkeys():
                    if k3[0]=='s':
                        numSource=numSource+1
                newModulator="m%d"%(int(numSource)+1)
                newSource   ="s%d"%(numSource+1)
                if not 'traffic' in RouterDict[Flow[1]]:
                    RouterDict[Flow[1]]['traffic']=[[]]
                ##
                RouterDict[Flow[1]]['traffic']+=[[newModulator]]
                RouterDict[Flow[1]][newModulator]=[["modulator start=0.0 generator=%s profile=((10,),(1,))"%(newSource)]]
                RouterDict[Flow[1]][newSource]=[]
                RouterDict[Flow[1]][newSource].append(["harpoon"])
                RouterDict[Flow[1]][newSource].append(["ipsrc=%d.%d.%d.0/24"%((counter/40000)%200+1,(counter/200)%200+1,counter%200+1)])
                RouterDict[Flow[1]][newSource].append(["ipdst=%d.%d.%d.0/24"%((counter/40000)%200+1,(counter/200)%200+1,counter%200+6)])
                RouterDict[Flow[1]][newSource].append(["flowsize=pareto(%d,1.2)"%float(Flow[3])])
                RouterDict[Flow[1]][newSource].append(["flowstart=exponential(100.0)"])
                ##RouterDict[Flow[1]][newSource].append(["flowstart=normal(1,%d)"%(float(Flow[0])/1000.0+2.0)])
                RouterDict[Flow[1]][newSource].append(["ipproto=randomchoice(6)"])
                RouterDict[Flow[1]][newSource].append(["sport=randomchoice(22,80,443)"])
                RouterDict[Flow[1]][newSource].append(["dport=randomunifint(1025,65535)"])
                RouterDict[Flow[1]][newSource].append(["lossrate=randomchoice(0.001)"])
                ##
                SRouterDict[Flow[1]]= RouterDict[Flow[1]]
                if Flow[1] in DRouterDict:
                    DRouterDict[Flow[1]]= RouterDict[Flow[1]]

            else: ##Case 2: if source-router exists in R and not in S: Add source in R. copy it to S
                RouterDict[Flow[1]]['traffic']= [['m1 ']]
                RouterDict[Flow[1]]['m1']=[["modulator start=0.0 generator=s1 profile=((10,),(1,))"]]
                RouterDict[Flow[1]]['s1']=[]
                RouterDict[Flow[1]]['s1'].append(["harpoon "])
                RouterDict[Flow[1]]['s1'].append(["ipsrc=%d.%d.%d.0/24"%((counter/40000)%200+1,(counter/200)%200+1,counter%200+1)])
                RouterDict[Flow[1]]['s1'].append(["ipdst=%d.%d.%d.0/24"%((counter/40000)%200+1,(counter/200)%200+1,counter%200+6)])
                RouterDict[Flow[1]]['s1'].append(["flowsize=pareto(%d,1.2)"%float(Flow[3])])
                RouterDict[Flow[1]]['s1'].append(["flowstart=exponential(100.0)"])
                RouterDict[Flow[1]]['s1'].append(["ipproto=randomchoice(6)"])
                RouterDict[Flow[1]]['s1'].append(["sport=randomchoice(22,80,443)"])
                RouterDict[Flow[1]]['s1'].append(["dport=randomunifint(1025,65535)"])
                RouterDict[Flow[1]]['s1'].append(["lossrate=randomchoice(0.001)"])
                ##
                SRouterDict[Flow[1]]= RouterDict[Flow[1]]
                DRouterDict[Flow[1]]= RouterDict[Flow[1]]
        else: ##Case3  : Add router in S. copy to R
            SRouterDict[Flow[1]]={'autoack': [['False']],'ipdests':[],'traffic':[['m1 ']],'m1':[],'s1':[]}
            SRouterDict[Flow[1]]['m1']=[["modulator start=0.0 generator=s1 profile=((10,),(1,))"]]
            SRouterDict[Flow[1]]['s1'].append(["harpoon"])
            SRouterDict[Flow[1]]['s1'].append(["ipsrc=%d.%d.%d.0/24"%((counter/40000)%200+1,(counter/200)%200+1,counter%200+1)])
            SRouterDict[Flow[1]]['s1'].append(["ipdst=%d.%d.%d.0/24"%((counter/40000)%200+1,(counter/200)%200+1,counter%200+6)])
            SRouterDict[Flow[1]]['s1'].append(["flowsize=pareto(%d,1.2)"%float(Flow[3])])
            SRouterDict[Flow[1]]['s1'].append(["flowstart=exponential(100.0)"])
            SRouterDict[Flow[1]]['s1'].append(["ipproto=randomchoice(6)"])
            SRouterDict[Flow[1]]['s1'].append(["sport=randomchoice(22,80,443)"])
            SRouterDict[Flow[1]]['s1'].append(["dport=randomunifint(1025,65535)"])
            SRouterDict[Flow[1]]['s1'].append(["lossrate=randomchoice(0.001)"])
            ##
            RouterDict[Flow[1]] = SRouterDict[Flow[1]]
######################################################################################################################
        if Flow[2] in RouterDict:
            if Flow[2] in DRouterDict: ## Case 1: If dest-router exists in D (and R): Add new ipdest
                if not 'ipdests' in RouterDict[Flow[2]]:
                   RouterDict[Flow[2]]['ipdests']= []
                RouterDict[Flow[2]]['ipdests'].append(["%d.%d.%d.0/16 "%((counter/40000)%200+1,(counter/200)%200+1,counter%200+1)])
                ##
                DRouterDict[Flow[2]] = RouterDict[Flow[2]]
                if Flow[2] in SRouterDict:
                    SRouterDict[Flow[2]] = RouterDict[Flow[2]]
            else: ## Case 2: if dest-router exists in R and not in D(ie it was source-router) Add ipdest in R. copy it to D
                if not 'ipdests' in RouterDict[Flow[2]]:
                   RouterDict[Flow[2]]['ipdests']=[]
                RouterDict[Flow[2]]['ipdests'].append(["%d.%d.%d.0/16 "%((counter/40000)%200+1,(counter/200)%200+1,counter%200+1)])
                ##
                DRouterDict[Flow[2]] = RouterDict[Flow[2]]
                SRouterDict[Flow[2]] = RouterDict[Flow[2]]
        else: ## Case 3: if dest-router NOT exists in R : Add router in D. copy to R
            DRouterDict[Flow[2]]={'autoack': [['False']], 'ipdests':[]}
            DRouterDict[Flow[2]]['ipdests'].append(["%d.%d.%d.0/16 "%((counter/40000)%200+1,(counter/200)%200+1,counter%200+1)])
            ##
            RouterDict[Flow[2]] = DRouterDict[Flow[2]]

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
            PropertyStr+= ' '
        print "\t"+k1+"="+"\""+str(PropertyStr)+"\""
    print"];"

for line in fj:
    if line!= "":
        Link=line.split(" ")
        print Link[0]+ " -- "+Link[1]+"[weight ="+Link[2]+", capacity ="+Link[3]+", delay ="+str(float(Link[4])),
        print "];"
print "}\n"



