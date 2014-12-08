#!/usr/bin/python
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
            RouterDict[LinkList[1]]['s']+="ipdst=10.1.0.0/162 "
            RouterDict[LinkList[1]]['s']+="flowsize=pareto(10000, 1.2) "
            RouterDict[LinkList[1]]['s']+="flowstart=exponential(100.0) "
        else:
            RouterDict[LinkList[1]]={'autoack': "False", 'ipdests':"", 'traffic':"m", 'm': "", 's':""}
            RouterDict[LinkList[1]]['m']="modulator start=0.0 generator=s profile=((3600,),(1,))"
            RouterDict[LinkList[1]]['s']="harpoon ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) lossrate=randomchoice(0.001)"

        if LinkList[2] in RouterDict:
            RouterDict[LinkList[2]]['traffic']="m2"
        else:
            RouterDict[LinkList[2]]={'autoack': [False], 'ipdests':[] , 'traffic':['m'], 'm': [], 's':[]}
            RouterDict[LinkList[2]]['m']=["modulator start=0.0 generator=s profile=((3600,),(1,)) "]
            RouterDict[LinkList[2]]['s'].append(["harpoon "])
            RouterDict[LinkList[2]]['s'].append(["ipproto=randomchoice(6) "])
            RouterDict[LinkList[2]]['s'].append(["sport = randomchoice(22, 80, 443) "])
            RouterDict[LinkList[2]]['s'].append(["dport = randomunifint(1025, 65535) "])
            RouterDict[LinkList[2]]['s'].append(["lossrate = randomchoice(0.001) "])