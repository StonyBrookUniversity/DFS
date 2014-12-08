import sys
import random
from random import randint
fi = open("tree15", "r")
fj = open("tree15", "r")

fo = open("tree15.dot", "wb")
sys.stdout=fo
RouterList =[] 

print "graph test {"
print "flowexport=text"
print "counterexportfile=\"counters\""
print "counterexport=True"
print "counterexportinterval=1"
#print "measurementnodes=\"H1 H2\""

line = fi.readline()
line = fi.readline()

for line in fi:
    if line.strip()!= "":
        Flow=line.strip().split(" ")
        Router='H'+Flow[0].strip('S')
        if Router not in RouterList:
            RouterList.append(Router)

for Router in RouterList:
    print Router,
    print "["
    print "autoack=\"False\""
    num=int(Router.strip('H'))
    print "ipdests=\"10.1.%d.0/24\""%((num+5)%240+1)
    print "traffic=\"m1\""
    print "m1=\"modulator start=0.0 generator=s1 profile=((1,),(1,))\""
    print "s1=\"harpoon ipsrc=10.1.%d.0/24 ipdst=10.1.%d.0/16 flowsize=normal(1000000000,.0001) flowstart=normal(.01,.0001) ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) tcpmodel=csa00\""%(num%240,randint(1,240))
    print"];"

for line in fj:
    if line!= "":
        Link=line.split(" ")
        if Link[0][0]=='S' and Link[1][0]=='S':
            print 'H'+Link[0].strip('S')+ " -- "+'H'+Link[1].strip('S')+"[weight ="+str(10)+", capacity ="+str(1000000000)+", delay ="+"0.01"+"]"

print "}\n"

