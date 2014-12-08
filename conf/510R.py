# Open a file
f = open("510R.dot", "wb")
f.write("graph test {\n")
f.write("\nflowexport=text\n")

f.write("\n//Topology with 510 Routers r1-r510  \n")
for i in range(1,255):
    f.write('r%i[\n\tautoack = "False"\n\tipdests = "10.0.%i.0/16"\n];\n'%(i,i))
for i in range(1,255):
    f.write('r%i[\n\tautoack = "False"\n\tipdests = "10.1.%i.0/16"\n];\n'%(i+255,i))

f.write("\n\nLinks\n\n")

f.write("}")
