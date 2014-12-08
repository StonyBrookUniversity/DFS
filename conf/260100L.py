# Open a file
f = open("260100L.dot", "wb")
f.write("graph test {\n")
f.write("\nflowexport=text\n")

f.write("\n//Topology with 510 Routers r1-r510  \n")
for i in range(1,255):
    f.write('r%d[\n\tautoack = "False"\n\tipdests = "10.0.%d.0/16"\n];\n'%(i,i))
for i in range(1,255):
    f.write('r%d[\n\tautoack = "False"\n\tipdests = "10.1.%d.0/16"\n];\n'%(i+255,i))

f.write("\n\nLinks\n\n")

for i in range(1,510):
    for j in range(1, 510):
            if i!=j:
                f.write('\tr%d - - r%d[weight = 1, capacity = 100000000, delay = 0.001];\n'%(i,j))

f.write("}")
