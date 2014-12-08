import sys
trafficmatrix = open('traffic.matrix', 'r')
fo = open("input2.matrix", "wb")
sys.stdout=fo
flowList = []
matrixList=[]
matrixList.append([])
matrixList.append([])
matrixList.append([])
matrixList.append([])


for line in trafficmatrix:
    if line.strip()!= "":
        flowList.append(line.strip().split(" "))

for item in  flowList:
    matrixList[0].append(item[0])
    matrixList[1].append("10.1.1.%d"%(int(item[1].strip().strip('H'))%254))
    matrixList[2].append("10.1.1.%d"%(int(item[2].strip().strip('H'))%254))
    matrixList[3].append(item[3])



for i in  range(len(matrixList[0])):
    print matrixList[0][i],
    print matrixList[1][i],
    print matrixList[2][i],
    print matrixList[3][i]