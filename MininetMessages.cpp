
#pragma warning(disable:4503)
#pragma warning(disable:4018)



#include "navidConstants.h"
#include "networkControlLogic2.h"

/*
struct message {
	int currentHop;
	int nextHop;
	int destination;
	int source;
	int type;
	string flowID;
	Sim_Timer idleTimeOut;
	Sim_Timer hardTimeOut;
};//*/

/*message Types

type=1 Message is from currentHop to destination the nexthop is nextHop;
type=2 Message is from currentHop to destination for flow f the nexthop is nextHop;

//*/


void networkControlLogic2::miniNetRuleUpdate1(int s,int i,int j){
	static message f;
	f.currentHop=s;
	f.destination=i;
	f.nextHop=j;
	f.type=1;
	f.priority=2;
	f.idleTimeOut=0;
	f.hardTimeOut=0;
	f.flowID="";
	f.source=s;
	this->newMessages.push_back(f);
}

void networkControlLogic2::miniNetRuleUpdateFlowRules1(flowPtr g,int currentHop,int nextHop){
	message f;
	f.currentHop=currentHop;
	f.destination=g->destination;
	f.nextHop=nextHop;
	f.type=2;
	f.priority=1+PRIORITY_SHIFT;
	f.idleTimeOut=FLOW_IDLE_TIMEOUT;
	f.hardTimeOut=0;
	f.flowID=g->flowID;
	f.source=g->source;
	this->newMessages.push_back(f);
}


void networkControlLogic2::miniNetRuleUpdateFlowRules2(flowPtr g,int currentHop,int nextHop) {
	//this one is called when a flow is ended and all the rules corresponding to flow are getting deleted.
	//right now it implemented using the idle timer and the ruless are not  deleteed
}

void networkControlLogic2::miniNetRuleUpdateLinkDelete(int s,int d) {
	//this funciton is called when the link is being deleted.
}
