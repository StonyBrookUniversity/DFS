#!/usr/bin/python
import re
fi = open("tree8", "r")
fo = open("tree8.dot", "wb")
fo.write("graph test {\n")
fo.write("\nflowexport=text\n")


line = fi.readline()
line = fi.readline()

line = fi.readline()

while line!= 0:
    RouterList = re.sub("[^\w]", " ",  line).split()
    fo.write('%s[\n\tautoack = "False"\n\tipdests = "10.0.0.0/16"\n];\n' % RouterList[0])
    fo.write('%s[\n\tautoack = "False"\n\tipdests = "10.0.0.0/16"\n];\n' % RouterList[1])
    fo.write('\t%s -- %s[weight = 1, capacity = 100000000, delay = 0.001];\n'%(RouterList[0],RouterList[1]))

fo.write("}")
