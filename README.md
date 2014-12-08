# DFS: a network flow simulaor for Datacentre
FS is a network flow record generator designed by joel sommers (https://github.com/jsommers/fs). It contains a discrete event simulation core to generate the flow records, and relies on existing TCP throughput models to drive the simulation.
I designed DFS on the top of FS to make it work with various Data centre topologies and to work with custom SDN controller Written in C++ STl using the Python Boost Interface. It was a part of our project "Firefly" selected in SIGCOMM 2014.

YOUTUBE LINK
https://www.youtube.com/watch?v=BpALE-FkkwI
    
##The Original README file is README.fs

##########################################################
Run the fs Simulations
############################################################

1) First we create the topology and to do so we do the following:

TOPOLOGY GENERATION
1 open the python script conf/trafficlogicinput.py .
2 Update the traffic matrix and topology file information. 

fi = open("traffic_uniform.txt", "r")
trafficmatrix = open('traffic_uniform.txt', 'r')
fo = open("traffic_logic.dot", "wb")

Update the topology parameters and algorithm to be used.

initTopology=networkControlLogic2object.initTopology
for i in range(0,64):

3 Run the script. It will create  2 files traffic_logic.dot and input.matrix.


4 cd to fs root directory and run fs
$ python -OO fs.py -t 600 conf/traffic_logic.dot
