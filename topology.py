import sys
import random
fi = open("tree30", "r")
fj = open("tree30", "r")

fo = open("tree30.dot", "wb")
sys.stdout=fo
RouterList =[] 

print "graph test {"
print "flowexport=text"
print "counterexportfile=\"counters\""
print "counterexport=True"
print "counterexportinterval=1"
print "measurementnodes=\"H1 H2\""

line = fi.readline()
line = fi.readline()

for line in fi:
    if line!= "":
        Flow=line.split(" ")
        if Flow[0] not in RouterList:
            Router='H'+Flow[0].strip('S')
            RouterList.append(Router)

for Router in RouterList:
    print Router,
    print "["
    print "autoack=\"False\""
    num=int(Router.strip('H'))
    print "ipdests=\"10.1.%d.0/24\""%(num%200)
    print "traffic=\"m1\""
    print "m1=\"modulator start=0.0 generator=s1 profile=((1,),(1,))\""
    print "s1=\"harpoon ipsrc=10.1.%d.0/24 ipdst=10.1.0.0/16 flowsize=pareto(10000,1.2) flowstart=exponential(100.0) ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) lossrate=randomchoice(0.0001)\""%(num%200)
    print"];"

for line in fj:
    if line!= "":
        Link=line.split(" ")
        if Link[0][0]=='S' and Link[1][0]=='S':
            print 'H'+Link[0].strip('S')+ " -- "+'H'+Link[1].strip('S')+"[weight ="+str(10)+", capacity ="+str(100000000)+", delay ="+"0.00001"+"]"

print "}\n"
