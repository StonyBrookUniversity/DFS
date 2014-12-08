import sys
import random
import networkControlLogic2module

networkControlLogic2object = networkControlLogic2module.networkControlLogic2class()
print networkControlLogic2module
print networkControlLogic2module.networkControlLogic2class
print networkControlLogic2object
print networkControlLogic2object.initilize


print networkControlLogic2object.initilize(64,16,8,networkControlLogic2module.oursCongestion)

print "Hi"
print networkControlLogic2object.initTopology

print networkControlLogic2object.RoutingTable[0][2][0].first
networkControlLogic2object.RoutingTable[0][2][0].first =5
print networkControlLogic2object.RoutingTable[0][2][0].first

networkControlLogic2object = networkControlLogic2module.networkControlLogic2class()
networkControlLogic2object.initilize(32,8,4,networkControlLogic2module.oursNoFlowRouting)
initTopology=networkControlLogic2object.initTopology


networkControlLogic2object = networkControlLogic2module.networkControlLogic2class()
networkControlLogic2object.initilize(32,8,4,networkControlLogic2module.oursNoFlowRouting)
print networkControlLogic2object.trafficVolume
print networkControlLogic2object.elephentsNum
print networkControlLogic2object.elephentsVolume
print networkControlLogic2object.trafficVolumeInTransit
print networkControlLogic2object.elephentsNumInTransit
print networkControlLogic2object.elephentsVolumeInTransit

print networkControlLogic2object.elephantFlowArrival
print networkControlLogic2object.elephantFlowEnd
print networkControlLogic2object.nextTimer
ft=1.6
print networkControlLogic2object.computTopo(long(ft))

#for i in range(0,32):
#    print "%d H%d H%d 10000"%(i,i+1,random.randint(1,32))
"""

print networkControlLogic2object.trafficVolume

print networkControlLogic2module.vectorSizeCalc(networkControlLogic2object.RoutingTable[0][2])

print networkControlLogic2object.RoutingTable[0][2][0]
print networkControlLogic2object.RoutingTable[0][2][1]
print networkControlLogic2object.RoutingTable[0][2][2]
print "Fun"
print networkControlLogic2object.FlowRoutingTable[0]['10.1.1.31 10.1.1.20 6 5155 17435']"""