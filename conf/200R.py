# Open a file
f = open("200R.dot", "wb")
f.write("graph test {\n")
f.write("\nflowexport=text\n")

f.write("\n//Topology with 200 Routers r1-r510  \n")
for i in range(1,200):
    f.write('r%i[\n\tautoack = "False"\n\tipdests = "10.0.%i.0/16"\n];\n'%(i,i))

f.write("\n\nLinks\n\n")

f.write("}")