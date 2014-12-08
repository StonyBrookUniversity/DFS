#!/usr/bin/python
import random
fi = open("traffic_matrix_001", "r")
fo = open("traffic_matrix_001.dot", "wb")
fo.write("graph test {\n")
print "graph test {\n"
fo.write("\nflowexport=text\n")
print "\nflowexport=text\n"

RouterDict = dict()

for line in fi:
    if line!= "":
        counter=0
        LinkList =line.split(" ")
        if LinkList[1] in RouterDict:
            RouterDict[LinkList[1]]['s'].append(["ipdst=10.%d.0.0/16"%(random.randint(1, 255))])
            RouterDict[LinkList[1]]['s'].append(["flowsize=%d"%float(LinkList[3])])
            RouterDict[LinkList[1]]['s'].append(["flowstart=exponential(%d)"%(float(LinkList[0])/1000)])
        else:
            counter += 1
            RouterDict[LinkList[1]]={'autoack': ['False'], 'ipdests':[] , 'traffic':[['m']], 'm': [], 's':[]}
            RouterDict[LinkList[1]]['m']=[["modulator start=0.0 generator=s profile=((3600,),(1,)) "]]
            RouterDict[LinkList[1]]['s'].append(["harpoon "])
            RouterDict[LinkList[1]]['s'].append(["ipsrc=10.%d.0.0/16"%(counter)])
            RouterDict[LinkList[1]]['s'].append(["ipdst=10.%d.0.0/16"%(random.randint(1, 255))])
            RouterDict[LinkList[1]]['s'].append(["flowsize=%d"%float(LinkList[3])])
            RouterDict[LinkList[1]]['s'].append(["flowstart=exponential(%d)"%(float(LinkList[0])/1000)])
            RouterDict[LinkList[1]]['s'].append(["ipproto=randomchoice(6) "])
            RouterDict[LinkList[1]]['s'].append(["sport = randomchoice(22, 80, 443) "])
            RouterDict[LinkList[1]]['s'].append(["dport = randomunifint(1025, 65535) "])
            RouterDict[LinkList[1]]['s'].append(["lossrate = randomchoice(0.001) "])


        if LinkList[2] in RouterDict:
            RouterDict[LinkList[2]]['traffic']=[["m2"]]
            RouterDict[LinkList[2]]['ipdests'].append(["10.%d.0.0/16"%(random.randint(1, 255))])
        else:
            RouterDict[LinkList[2]]={'autoack': [['False']], 'ipdests':[] , 'traffic':[['m']], 'm': [], 's':[]}
            RouterDict[LinkList[2]]['m']=[["modulator start=0.0 generator=s profile=((3600,),(1,)) "]]
            RouterDict[LinkList[2]]['ipdests'].append(["10.%d.0.0/16"%(random.randint(1, 255))])

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

fo.write("}\n")
print "}\n"

