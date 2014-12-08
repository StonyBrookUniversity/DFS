import sys
import re
from subprocess import Popen, PIPE
import os.path
import glob


f = open("trafficReport.txt","wb")
sys.stdout=f

print "Creating Router Report"
for i in range(1,65):#num routers+1
    ff = open("H%d_flow.txt"%i,"r")
    fd = open("H%d_duration.txt"%i,"wb")
    for line in ff:
        if line.strip()!= "":
            Flowlet=line.strip().split(" ")
            IP=Flowlet[5].split('->')
            fd.write(str(float(Flowlet[4])-float(Flowlet[3])))
            fd.write("\n")

    byteCount=0
    packetCount=0
    flowCount=0
    fc = open("H%d_counters.txt"%i,"r")
    for line in fc:
        if line.strip()!= "":
            Counter=line.strip().split(" ")
            byteCount=byteCount+int(Counter[2])
            packetCount=packetCount+int(Counter[4])
            flowCount=flowCount+int(Counter[6])
    print "\nH%d"%i,
    print "ByteCount:"+str(byteCount/(1024*1024))+"MB",
    print "PacketCount:"+str(packetCount/1024)+"K",
    print "FlowCount:"+str(flowCount)+"Units",

print("\n")
for i in range(1,65):
    for j in range(1,65):
        if i==j:
            transferString='harpoon->H%d'%(j)
        else:    
            transferString='H%d->H%d'%(i,j)
        inputFile='H%d_counters.txt'%j
        outFile='H%dH%d.txt'%(i,j)
        #print transferString
        #print inputFile
        #print outFile
        temp = open(outFile, "wb")

        for line in open(inputFile, 'r'):
            if re.search(transferString, line):
                temp.write(line)

print("\n")
print "Creating Flow  Report"
for i in range(1, 65):
    for j in range(1, 65):
        byteCount = 0
        packetCount = 0
        flowCount = 0
        outFile='H%dH%d.txt'%(i,j)
        for line in open(outFile, 'r'):
            if line.strip() != "":
                Counter = line.strip().split(" ")
                byteCount = byteCount + int(Counter[2])
                packetCount = packetCount + int(Counter[4])
                flowCount = flowCount + int(Counter[6])
        print '\nH%d->H%d'%(i,j),
        print "ByteCount:" + str(byteCount/(1024*1024)) + "MB",
        print "PacketCount:" + str(packetCount/1024) + "K",
        print "FlowCount:" + str(flowCount) + "Units",

    """
    for i in range(1, 15):
    p = Popen(['grep', '"H1->H1"', '"H1_counters.txt"'], stdin=PIPE, stdout=PIPE,stderr=PIPE)

    #cmd_line = ['grep', '-i', '--line-buffered', 'H1->H1'] + glob.glob('*_counters.txt')
    #process = Popen(cmd_line)
    #print cmd_line
    """
    """
    for j in range(1,15):
        transferString='H%d->H%d'%(j,i)
        inputFile='H%d_counters.txt'%i
        print transferString
        print inputFile
        if os.path.isfile(inputFile):
            process = Popen(['grep', "H1->H1", "H1_counters.txt"], stdout=temp)
            #process = Popen(['grep', transferString, inputFile], stdout=temp)
            #process = Popen(['grep', 'H%d->H%d'%(j,i), 'H%d_counters.txt'%i], stdout=temp)
        stdout, stderr = process.communicate()	    
        
        for line in temp:
            if line.strip()!= "":
                tempLine=line.strip().split(" ")
                print tempLine
    """
