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
########################################################################################################################
# "" Creating DOT File""
########################################################################################################################
"""
Initial Processing
"""
NETWORKSIZE=64
FSONum=48
MirrorNum=10
fo = open("traffic_logic.dot", "wb")
foback=sys.stdout
sys.stdout=fo

print "graph test {"
print "flowexport=text"
print "counterexportfile=\"counters\""
print "counterexport=True"
print "counterexportinterval=1"
"""
Node Description And Traffic Generation Code
"""
for i in range(1,NETWORKSIZE+1):  ##Num of Routers
    Nodename= 'H'+str(i)
    print Nodename,"["
    print "autoack=\"False\""
    print "ipdests=",nodename_to_ipaddr(Nodename)
    print "traffic=\"",
    for j in range(1,2*NETWORKSIZE+1):#traffic
        print "m"+str(j),
    print "\""

    for j in range(1,NETWORKSIZE+1):#modulator and source
        print "m"+str(2*j-1)+"=\"modulator start=0.0 generator=s"+str(2*j-1)," profile=((60,),(1,))\""
        print "s"+str(2*j-1)+"=\"harpoon ipsrc=",nodename_to_ipaddr(Nodename)," ipdst="+nodename_to_ipaddr("H"+str(j))," flowsize=normal(1000000000,10000000) flowstart=normal(.01,0) ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) lossrate=randomchoice(.001)\""
        print "m"+str(2*j)+"=\"modulator start=0.0 generator=s"+str(2*j)," profile=((60,),(1,))\""
        print "s"+str(2*j)+"=\"harpoon ipsrc=",nodename_to_ipaddr(Nodename)," ipdst=",nodename_to_ipaddr("H"+str(j))," flowsize=normal(2000,100) flowstart=normal(.5,0) ipproto=randomchoice(6) sport=randomchoice(22,80,443) dport=randomunifint(1025,65535) lossrate=randomchoice(.001)\""
    print "];"

"""
Topology Generation Code
"""
#import networkControlLogic2module

#networkControlLogic2object = networkControlLogic2module.networkControlLogic2class()
#networkControlLogic2object.initilize(64,16,8,networkControlLogic2module.oursCongestion)
initTopology=networkControlLogic2object.initTopology
for i in range(1,NETWORKSIZE+1):
    for j in range(1,i):
        if initTopology[i-1][j-1]:
            print "H%d -- H%d[weight=10, capacity=100000000, delay=0.00005];"%(i,j)
#print "}\n"
"""
initAdditionalTopology=networkControlLogic2object.initAdditionalTopology
for i in range(1,NETWORKSIZE+1):
    for j in range(0,i):
        if initAdditionalTopology[i-1][j-1]:
            print "H%d -- H%d[weight=10, capacity=1000000, delay=0.00005];"%(i,j)
"""
print "}\n"


sys.stdout=foback

import fs
options= {'simtime': 600, 'interval': 0.02, 'configonly': False, 'seed': None, 'debug': 0, 'logfile': ''}
args=['conf/traffic_logic.dot']
fs.main()
print "Hi"
