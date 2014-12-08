from itertools import chain
from trafgen import TrafficGenerator
import socket
import ipaddr
from fslib.common import fscore, get_logger
from fslib.flowlet import Flowlet, FlowIdent
from copy import copy
from importlib import import_module
from fslib.util import *
import sys

haveIPAddrGen = False
try:
    import ipaddrgen
    haveIPAddrGen = True
except:
    pass

class MatrixTrafficGenerator(TrafficGenerator):
    def __init__(self, srcnode, ipsrc='0.0.0.0', ipdst='0.0.0.0', sport=0, dport=0, flowstarttime=0, flowsize=1500, pktsize=1500, flowstart=0, ipproto=socket.IPPROTO_TCP, lossrate=0.0045, mss=1460, iptos=0x0, xopen=True, tcpmodel='csa00',matrix='../conf/input.matrix'):
        TrafficGenerator.__init__(self, srcnode)
        self.logger = get_logger('fs.matrix')

        trafficmatrix = open(matrix, 'r')
        flowList = []
        flowStartList = []
        srcipList = []
        dstipList = []
        flowSizeList = []

        for line in trafficmatrix:
            if line.strip()!= "":
                flowList.append(line.strip().split(" "))

        for item in  flowList:
            try:
                if nodename_to_ipaddr(srcnode)==item[1]:
                    flowStartList.append(item[0])
                    srcipList.append(item[1])
                    dstipList.append(item[2])
                    #srcipList.append(nodename_to_ipaddr(item[1]))
                    #dstipList.append(nodename_to_ipaddr(item[2]))
                    flowSizeList.append(item[3])
            except:
                print "Invalid Flow"
                print item
                pass

        self.srcipList=srcipList

        self.srcnet = eval('sequentialchoice(srcipList)')
        self.dstnet = eval('sequentialchoice(dstipList)')
        self.flowstarttimerv = eval('sequentialchoice(flowStartList)')
        self.flowsizerv = eval('sequentialchoice(flowSizeList)')

        if haveIPAddrGen:
            self.ipsrcgen = ipaddrgen.initialize_trie(int(self.srcnet), self.srcnet.prefixlen, 0.61)
            self.ipdstgen = ipaddrgen.initialize_trie(int(self.dstnet), self.dstnet.prefixlen, 0.61)

        if isinstance(ipproto, (str,unicode)):
            #print eval(ipproto)
            self.ipproto = eval(ipproto)
        else: 
            self.ipproto = randomchoice(ipproto)

        if isinstance(sport, (str,unicode)):
            self.srcports = eval(sport)
        else:
            self.srcports = randomchoice(sport)

        if isinstance(dport, (str,unicode)):
            self.dstports = eval(dport)
        else:
            self.dstports = randomchoice(dport)

        if isinstance(pktsize, (str,unicode)):
            self.pktsizerv = eval(pktsize)
        else:
            self.pktsizerv = randomchoice(pktsize)

        if isinstance(flowstart, (str,unicode)):
            self.flowstartrv = eval(flowstart)
        else:
            self.flowstartrv = randomchoice(flowstart)

        if isinstance(lossrate, (str,unicode)):
            self.lossraterv = eval(lossrate)
        else:
            self.lossraterv = randomchoice(lossrate)

        if isinstance(mss, (str,unicode)):
            self.mssrv = eval(mss)
        else:
            self.mssrv = randomchoice(mss)

        if isinstance(iptos, (str,unicode)):
            self.iptosrv = eval(iptos)
        else:
            self.iptosrv = randomchoice(iptos)

        self.xopen = xopen
        self.activeflows = {}

        try:
            self.tcpmodel = import_module("tcpmodels.{}".format(tcpmodel))
        except ImportError,e:
            raise InvalidFlowConfiguration('Unrecognized tcp model for matrix: {} (Error on import: {})'.format(tcpmodel, str(e)))


    def start(self):
        startt = next(self.flowstartrv)
        if self.srcipList!=[]:
            fscore().after(startt, 'matrix-start'+str(self.srcnode), self.newflow)


    def newflow(self, xint=1.0):
        if self.done:
            print 'matrix generator done'
            return
        flet=""
        try:
            flet = self.__makeflow()
        except:
            return 
        if flet is None:
            return
        self.activeflows[flet.key] = 1
        owd=0
        destnode = fscore().topology.destnode(self.srcnode, flet.dstaddr)
        try:
            owd = fscore().topology.owd(self.srcnode, destnode)
        except:
            pass
        print "owd is",owd
        # owd may be None if routing is temporarily broken because of
        # a link being down and no reachability
        if owd==0 :
            owd = 1.0 
        if owd is None :
            owd = 1.0 

        flet.mss = next(self.mssrv)
        p = next(self.lossraterv)
        basertt=0

        try:    
            basertt = owd * 2.0
        except:
            basertt = 2.0
            pass

        flowduration, byteemit = self.tcpmodel.model(flet.size, flet.mss, basertt, fscore().interval, p)
        #print flowduration
        #print flet.bytes

        # FIXME: add an end timestamp onto flow to indicate its estimated
        # duration; routers along path can add that end to arrival time to get
        # better flow duration in record.
        # unclear what to do with raw flows.
        flet.flowstart = flet.flowstarttime
        flet.flowend = flet.flowstart + flowduration
        #flet.flowstart = self.flowstarttimerv
        #flet.flowend = flet.flowstart +flowduration
        self.logger.debug("Flow duration: %f" % flowduration)
        try:
            if flet.iselephant==True:
                flowID=str(flet.key[0])+' '+str(flet.key[1])+' '+str(flet.key[2])+' '+str(flet.key[3])+' '+str(flet.key[4])
                #print "elephantFlowArrival"
                status=networkControlLogic2object.elephantFlowArrival(flowID,int(flet.key[0].split('.')[3])-1,int(flet.key[1].split('.')[3])-1,long((fscore().now+flet.flowstarttime)*(10**12)))
                print "networkControlLogic2object.elephantFlowArrival('",flowID,"',",int(flet.key[0].split('.')[3])-1,",",int(flet.key[1].split('.')[3])-1,",",long((fscore().now+flet.flowstarttime)*(10**12)),");"
                if status==0:
                    print "printf( \"elephantFlowArrival;Route table Not Changed\");"
                elif status==1:
                    print "print( \"elephantFlowArrival;Route table Changed\");"
                elif status==2:
                    print "printf( \"elephantFlowArrival;Some Error\");"

            fscore().after(0.0, 'flowemit-'+str(self.srcnode), self.flowemit, flet, 0, byteemit, destnode)
        except:
            print "Error calling networkControlLogic2object.elephantFlowArrival"
            pass

        # if operating in an 'open-loop' fashion, schedule next
        # incoming flow now (otherwise schedule it when this flow ends;
        # see code in flowemit())
        if self.xopen:
            nextst = next(self.flowstartrv)
            # print >>sys.stderr, 'scheduling next new matrix flow at',nextst
            fscore().after(nextst, 'newflow-'+str(self.srcnode), self.newflow)


    def flowemit(self, flowlet, numsent, emitrv, destnode):
        fsend = copy(flowlet)
        varemit=chain((emitrv), (0,)).next() 
        varflowlet=flowlet.bytes
        fsend.bytes = int(min(varemit,varflowlet)) 
        ## fsend.bytes = int(min(next(emitrv), flowlet.bytes)) 
        flowlet.bytes -= fsend.bytes
        try:
            networkControlLogic2object.trafficVolume[int(flowlet.srcaddr.split('.')[3])-1][int(flowlet.dstaddr.split('.')[3])-1]+= int(fsend.bytes*1.1)
            print "networkControlLogic2object.trafficVolume[",int(flowlet.srcaddr.split('.')[3])-1,"][",int(flowlet.dstaddr.split('.')[3])-1,"]+=",int(fsend.bytes*1.1),";"
            networkControlLogic2object.trafficVolumeInTransit[int(flowlet.srcaddr.split('.')[3])-1][int(flowlet.dstaddr.split('.')[3])-1]+= int(fsend.bytes*1.1)
            print "networkControlLogic2object.trafficVolumeInTransit[",int(flowlet.srcaddr.split('.')[3])-1,"][",int(flowlet.dstaddr.split('.')[3])-1,"]+=",int(fsend.bytes*1.1),";"
            if flowlet.iselephant==True:
                networkControlLogic2object.elephentsVolume[int(flowlet.srcaddr.split('.')[3])-1][int(flowlet.dstaddr.split('.')[3])-1]+= int(fsend.bytes*1.1)
                print "networkControlLogic2object.elephentsVolume[",int(flowlet.srcaddr.split('.')[3])-1,"][",int(flowlet.dstaddr.split('.')[3])-1,"]+=",int(fsend.bytes*1.1),";"
                networkControlLogic2object.elephentsVolumeInTransit[int(flowlet.srcaddr.split('.')[3])-1][int(flowlet.dstaddr.split('.')[3])-1]+= int(fsend.bytes*1.1)
                print "networkControlLogic2object.elephentsVolumeInTransit[",int(flowlet.srcaddr.split('.')[3])-1,"][",int(flowlet.dstaddr.split('.')[3])-1,"]+=",int(fsend.bytes*1.1),";"
        except:
            print "Error updating trafficVolume/trafficVolumeInTransit/elephentsVolume/elephentsVolumeInTransit"
            pass

        psize = min(next(self.pktsizerv), flowlet.mss)
        psize = int(max(40, psize))
        fsend.pkts = fsend.bytes / psize
        if fsend.pkts * psize < fsend.bytes:
            fsend.pkts += 1
        fsend.bytes += fsend.pkts * 40

        if flowlet.ipproto == socket.IPPROTO_TCP:
            flags = 0x0
            if numsent == 0: # start of flow
                # set SYN flag
                flags |= 0x02 

                # if first flowlet, add 1 3-way handshake pkt.
                # simplifying assumption: 3-way handshake takes place in one
                # simulator tick interval with final ack piggybacked with data.
                fsend.pkts += 1
                fsend.bytes += 40

            if flowlet.bytes == 0: # end of flow
                # set FIN flag
                flags |= 0x01

                fsend.pkts += 1
                fsend.bytes += 40

            # set ACK flag regardless
            flags |= 0x10 # ack
            fsend.tcpflags = flags

        numsent += 1

        self.logger.debug("sending %d bytes %d pkts %s flags; flowlet has %d bytes remaining" % (fsend.bytes, fsend.pkts, fsend.tcpflagsstr, flowlet.size))


        fscore().topology.node(self.srcnode).flowlet_arrival(fsend, 'matrix', destnode)

        # if there are more flowlets, schedule the next one
        if flowlet.bytes > 0:
            fscore().after(fscore().interval, "flowemit-{}".format(self.srcnode), self.flowemit, flowlet, numsent, emitrv, destnode)
        else:
            # if there's nothing more to send, remove from active flows 
            del self.activeflows[flowlet.key]

            # if we're operating in closed-loop mode, schedule beginning of next flow now that
            # we've completed the current one.
            if not self.xopen:
                fscore().after(next(self.flowstartrv), "newflow-{}".format(self.srcnode), self.newflow)
    
    def __makeflow(self):
        while True:
            # if haveIPAddrGen:
            #     srcip = str(ipaddr.IPv4Address(ipaddrgen.generate_addressv4(self.ipsrcgen)))
            #     dstip = str(ipaddr.IPv4Address(ipaddrgen.generate_addressv4(self.ipdstgen)))
            # else:
            #     # srcip = str(ipaddr.IPAddress(int(self.srcnet) + random.randint(0,self.srcnet.numhosts-1)))
            #     # dstip = str(ipaddr.IPAddress(int(self.dstnet) + random.randint(0,self.dstnet.numhosts-1)))
            #     # srcip = str(ipaddr.IPAddress(int(self.srcnet) + random.randint(0, 2)))
            #     # dstip = str(ipaddr.IPAddress(int(self.dstnet) + random.randint(0, 2)))
            srcip = next(self.srcnet)
            dstip = next(self.dstnet)

            ipproto = next(self.ipproto)
            sport = next(self.srcports)
            dport = next(self.dstports)
            fsize = int(next(self.flowsizerv))
            fstarttime = float(next(self.flowstarttimerv))

            #networkControlLogic2object.trafficNum[int(srcip.split('.')[3])-1][int(dstip.split('.')[3])-1]+=1

            flet = Flowlet(FlowIdent(srcip, dstip, ipproto, sport, dport), bytes=fsize, time=fstarttime)
            try:
                if fsize>ELEPHANTFLOWSIZE:
                    flet.iselephant=True
                    networkControlLogic2object.elephentsNum[int(srcip.split('.')[3])-1][int(dstip.split('.')[3])-1]+=1
                    print "networkControlLogic2object.elephentsNum[",int(srcip.split('.')[3])-1,"][",int(dstip.split('.')[3])-1,"]+=",1,";"
            except:
                print "Error Updating elephentsNum"
                pass

            #print "flettt",
            #print flet
            flet.iptos = next(self.iptosrv)
            if flet.key not in self.activeflows:
                break

        return flet

