import networkControlLogic2module

networkControlLogic2object = networkControlLogic2module.networkControlLogic2class()
networkControlLogic2object.initilize(32,8,4,networkControlLogic2module.oursNoFlowRouting)
initTopology=networkControlLogic2object.initTopology
for i in range(0,32):
    for j in range(0,i):
        if initTopology[i][j]:
            print "H%d -- H%d[weight=10, capacity=1000000000, delay=0.001]"%(i+1,j+1)
print "}\n"

print networkControlLogic2object.trafficVolume
print networkControlLogic2object.trafficVolume[0][1]