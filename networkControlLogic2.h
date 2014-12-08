#ifndef NETWORKCONTROLLERLOGIC2_H
#define NETWORKCONTROLLERLOGIC2_H







#include <algorithm> 
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <set>      // std::ifstream

//#include "netInterface.h"




#include <iostream>
#include <map>

#include <utility>

#include <string>
#include <stdlib.h>
#include <time.h>
#include "navidConstants.h"
#include <memory>

#include <random>
#include <assert.h>
#include <list>
#include <unordered_map>

//Interface C++ code
#include<vector>
#include "randomGraph.h"

//Version 1.2
#include <boost/python.hpp>

static int updateFlow=0;

using namespace std;

struct message {
	int currentHop;
	int nextHop;
	int destination;
	int source;
	int type;
	string flowID;
	int priority;
	Sim_Timer idleTimeOut;
	Sim_Timer hardTimeOut;
};

struct FSOSt{
	int d;
	short int FSO;
	short int SM;
	inline bool operator==(const FSOSt& rhs) {
		return ((d==rhs.d) && (FSO==rhs.FSO)&&(SM==rhs.SM));
    }

};

struct timeEvent{
	Sim_Timer t;
	int s;
	int d;
//	list<unordered_map<string,flow>::iterator> elephents;
};

struct edge{
	int s;
	int d;
	inline bool operator==(const edge& f) {
		return ((min(s,d)==min(f.s,f.d)) && (max(s,d)==max(f.s,f.d)));
    }

	edge(){};
	inline edge(int first,int second) {
		s=first;d=second;
	}
};
inline bool operator<(const edge& g,const edge& f) {
	return ((g.s<f.s) || ((g.s==f.s) && (g.d<f.d)));
};





struct flow{
	long long int flID;
	string flowID;
	int source;
	int destination;
	bool isRouted;
	list<edge> edgesUsed;
	set<edge> edgesUsed2;
	list<edge> waitingForActivation;
	flow() {isRouted=false;};

};

typedef flow* flowPtr;
typedef set<flowPtr>::iterator flowIt;



/*
inline bool operator<(const flowPtr& a,const flowPtr& b) {
	return a<b;
}
//*/



struct candidEdges {
	Sim_Timer t;
	bool inProcess;
	list<flowPtr> flows;
	list<FSOSt> FSOs;

};



void doSM(int n, int s, int& d);
void doRSM(int n, int s, int& d);


class networkControlLogic2 {
public:
	float ratio;
	trafficAlgorithm alg;
	int lastRun;
	long long int flID;
	const static int maxPath=MAX_NEXT_HOP;
	vector<int> visitedLeft;
	vector<int> visitedRight;
	list<vector<FSOSt> > routes;
	list<int> alternatePath;
	list<FSOSt> alterPath;
	vector<int> alternateBFS1;
	vector<int> alternateBFS2;
	bool isPriodicActive;
	vector<int> checked1;
	vector<int> checked2;
	int networkSize,FSONum,MirrorNum;
	Sim_Timer currentTime;
	Sim_Timer priodicTime;
	Sim_Timer nextReconfig;
	bool networkLocked;
	int augNetworkSize;

	bool routingNeedsUpdate;
	vector<vector<int> >  currentHop;
	vector<vector<vector< FSOSt> > > FSOGraph; //Graph in which each FSO mirror destination is marked
	vector<vector<int> > FSOLinks;
	vector<vector<int> > activeSM;
	list<int> hasChanged;
	vector<vector<set<flowPtr> > > flowsUsingThisEdge;
	vector<vector<set<flowPtr> > > flowsUsingThisEdge2;
	unordered_map<string,flow> elephentsInTheSystem;
	list<flowPtr> unprocessesFlows;
	vector<vector<candidEdges> > linksToBeActivated;
	

	Sim_Timer nextTimer;
	Sim_Timer lastReconfig;
	list<timeEvent> nextsCall;
	vector<vector<list <edge> > > beingUsed;
	void cmpTopoJellyfish(Sim_Timer t);
	void cmpTopocThrough(Sim_Timer t);
	void cmpTopotDBeam(Sim_Timer t);
	void cmpTopoOursCongestion(Sim_Timer t);
	void cmpoursNoFlowRouting(Sim_Timer t);
	void cmpourPriodicReconfig(Sim_Timer t);
	void processRoutesSecondaryPackets(int s, int d);

	void elATopoJellyfish(string flowID,int source, int destination,Sim_Timer time);
	void elATopocThrough(string flowID,int source, int destination,Sim_Timer time);
	void elATopotDBeam(string flowID,int source, int destination,Sim_Timer time);
	void elATopoOursCongestion(string flowID,int source, int destination,Sim_Timer time);
	void elAoursNoFlowRouting(string flowID,int source, int destination,Sim_Timer time);
	void elAourPriodicReconfig(string flowID,int source, int destination,Sim_Timer time); 
	void DeleteOpenTDBeam(int f);
	bool CheckOpenTDBeam(int f);
	void reRouteElephentAugment(flowPtr f);
	void reRouteElephent(flowPtr f);

	void DeleteOpencThrough(int f);
	bool CheckOpencThrough(int f);
	bool isMiniNet;
	bool isMininet;




public:
	vector<int> activateLinks;
	vector<vector<int> > topology;
	vector<vector<int> > initTopology;
	vector<vector<int> > additionalTopology;
	vector<vector<int> > initAdditionalTopology;
	vector<vector<long int> > trafficVolume;
	vector<vector<int> > elephentsNum;
	vector<vector<long int> > elephentsVolume;
	vector<vector<long int> > trafficVolumeInTransit;
	vector<vector<int> > elephentsNumInTransit;
	vector<vector<long int> > elephentsVolumeInTransit;
	vector<vector<int> > whichChanged;
	map<int, list<int> > augEdges;
	int totalAugmentLinks;

	vector< vector< set<int> > >	RoutingTableSet;
	vector< vector< vector<std::pair<int,int> > > >	RoutingTable;
	vector< vector< vector<std::pair<int,int> > > >	RoutingTable2;

	map<int, map<string, std::pair<int,int> > > FlowRoutingTable;

public:
	void initFattree();
	void readGraph();
	void constructLinks();
	void initateMemory();
	//void elephentsInSystem();
	bool findAlternatePath(int s,int j,bool isConnected(int,int));
	bool findAlternatePathInitialFSO(int s,int FSO);

	void BFSOneNodeUpdateRoutesUpdateAll();
	void BFSOneNodeUpdateRoutesUpdateAllAugment();

	bool isConnectedInitFSO(int i,int j);
	void addFSO(int s,int FSO);
	FSOSt debugfunc(FSOSt &g);
	bool checkConsist(void);
	bool isConnected();
	void BFSOneNodeUpdateRoutestDBeam(int s);
	void BFSOneNodeUpdateRoutescThrough(int s);
	void BFSOneNodeUpdateRoutes(int s);
	void BFSOneNodeUpdateRoutesAugment(int s);
	void miniNetRuleUpdate1(int s,int i,int j);

	void miniNetRuleUpdateFlowRules1(flowPtr f,int currentHop,int nextHop);
	void miniNetRuleUpdateFlowRules2(flowPtr f,int currentHop,int nextHop);

	void miniNetRuleUpdateLinkDelete(int s,int i);
	

//	void miniNetRuleUpdate1(int s,int i,int j);



	void networkControlLogic2::updateRoutingAddLinkCthrough(int s,int d);
	void networkControlLogic2::updateRoutingAddLinktDbeam(int s,int d);

	void deleteLink();
	void inittDbeam();
	void initcThrouh();
	void initJellyFish();	
	bool checkRemainConnected(int s, int d);
	bool checkConsistant();
	bool updateRoutingTable();
	vector<std::pair<int,string> > rulesToAdd;
	vector<std::pair<int,string> > rulesToDelete;
	vector<vector<vector<bool> > > routingHops;
	bool isFS;

public:
	void initilize(int networkSize,int FSONum,int MirrorNumber,trafficAlgorithm algo);
	void initilizeMiniNet(int networkSize,int FSONum,int MirrorNumber,trafficAlgorithm algo);
	void initilizeFS(int networkSize,int FSONum,int MirrorNumber,trafficAlgorithm algo);
	void initilizeAugmented(int networkSize, int FSONum, int MirrorNumber, trafficAlgorithm algo, float ratio);


	void reset();
	int  computTopo(Sim_Timer t);
	void processCTrhough();
	void process3dBeam();
	void updateRoutingDeletLink(int s,int d);
	void updateRoutingAddLink(int s,int d);
	void activateLink(timeEvent t);
	void activateLink(int s,int t);
	void addLink(const FSOSt& f,flowPtr fl);
	void addLinkCthrough(flowPtr fl);
	void addLinktDBeam(flowPtr fl);

	void activateLinkcThrough(int s,int d);
	void activateLinktDBeam(int s,int d);

	void routeElephent(flowPtr f);
	void routeElephentAugment(flowPtr f);

	void reRouteElephent(flowPtr f,int s);
	bool FSOInUse(const FSOSt& f);
	bool graphRemainConnected(const FSOSt& f);
	void deleteFSOLink(const FSOSt& f);
	bool processNextElephent(flowPtr f);
	bool processNextcThrough(flowPtr f);
	bool processNexttDBeam(flowPtr f);
	bool processNextElephentNoChange(flowPtr g);
	void processRoutesSecondaryPacketsFirst(int s,int d);


	void updateFlowTable();
	int elephantFlowArrival(string flowID,int source, int destination,Sim_Timer time);
	int elephantFlowEnd(string flowID,int source,int destination,Sim_Timer time);

	vector<vector<int> > distances;
	vector<vector<int> > numberOfRoutes;

	vector<message> newMessages;

	networkControlLogic2();
	~networkControlLogic2();
	/* Added by zafar */
	int get_FlowCount(int currentHop, string flowID);

};



#endif
