# FS: a network flow record generator
FS is a network flow record generator. It contains a discrete event simulation core to generate the flow records, and relies on existing TCP throughput models to drive the simulation.

## Running fs
To use fs, you need the following Python packages:
 * ipaddr
 * networkx
 * pydot
 * pyparsing
 * pytricia (py-radix is no longer supported)

To install all the above, see the requirements.txt file here and use pip:
    $ pip install -r requirements.txt

    
##The Original README file is README.md

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
