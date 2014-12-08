
#pragma warning(disable:4503)
#pragma warning(disable:4018)



#include "navidConstants.h"
#include "networkControlLogic2.h"
//#include "randomGraph.h"
//#define DEBUG
/*
void networkControlLogic2::updateFlowTable() {
	if (this->alg==jellyFish) return;
	int si=this->FlowRoutingTable.size();
	for (int i=0;i<si;i++) {
		int si=this->FlowRoutingTable[i].size();
		map<string, std::pair<int,int> >::iterator it;
		for (it=this->FlowRoutingTable[i].begin();it!=this->FlowRoutingTable[i].begin();it++) {
			if (this->alg==tDBeam) {
			}
			if (this->alg==cThrough) {
			{
				int g=this->topology[i][it->first];
				if (g!=-1) {
					if (g<it->second) {
					}
					else it->second=rand()%g;
				}
				else {
					//it->first=this->RoutingTable[i][it->first];
				}
			}
		}
	}
}
//*/
/*
inline bool operator<(const flowPtr& a,const flowPtr& b) {
	return a->flID<b->flID;
}

//*/


void networkControlLogic2::updateRoutingAddLink(int s,int d) {
	//*
	BFSOneNodeUpdateRoutesUpdateAll();
	routingNeedsUpdate=false;
	//BFSOneNodeUpdateRoutes(s);
	//BFSOneNodeUpdateRoutes(d);
	//*/
}
bool flipACoin() {
	if (rand()%2)
		return true;
	else return false;
}
void networkControlLogic2::deleteFSOLink(const FSOSt& f) {
	int active1=this->activeSM[f.d][f.FSO];
	if (active1>=0) {
		routingNeedsUpdate=true;
		FSOSt ff=this->FSOGraph[f.d][f.FSO][active1];
		this->topology[ff.d][f.d]--;
		this->topology[f.d][ff.d]--;

		this->activeSM[f.d][f.FSO]=-1;
		this->activeSM[ff.d][ff.FSO]=-1;
		//updateRoutingDeletLink(f.d,ff.d);
		if (this->topology[f.d][ff.d]==0) {
			processRoutesSecondaryPacketsFirst(f.d,ff.d);
			processRoutesSecondaryPackets(f.d,ff.d);
		}
	}
}
void networkControlLogic2::processRoutesSecondaryPacketsFirst(int s,int d) {
	flowIt it;
	for (it=this->flowsUsingThisEdge[s][d].begin();it!=this->flowsUsingThisEdge[s][d].end();it++) {
		int dest=(*it)->destination;
		if (s==dest) continue;
		pair<int,int> nextHop=this->RoutingTable[s][dest][rand()%RoutingTable[s][dest].size()];
		pair<int,int> preHop;
		preHop.first=s;
		this->FlowRoutingTable[preHop.first][(*it)->flowID]=nextHop;
		if (isMiniNet) 
			this->miniNetRuleUpdateFlowRules1(*it,preHop.first,nextHop.first);
		(*it)->edgesUsed.remove(edge(s,d));
		while (nextHop.first!=dest) {
			preHop=nextHop;
			nextHop=this->RoutingTable[preHop.first][dest][rand()%RoutingTable[preHop.first][dest].size()];
			this->FlowRoutingTable[preHop.first][(*it)->flowID]=nextHop;
			if (isMiniNet) 
				this->miniNetRuleUpdateFlowRules1(*it,preHop.first,nextHop.first);

			(*it)->edgesUsed.push_back(edge(preHop.first,nextHop.first));
		}
	}
	this->flowsUsingThisEdge[s][d].clear();
	this->flowsUsingThisEdge[d][s].clear();
}
void networkControlLogic2::processRoutesSecondaryPackets(int s,int d) {
	flowIt it;
	for (it=this->flowsUsingThisEdge2[s][d].begin();it!=this->flowsUsingThisEdge2[s][d].end();it++) {
		int dest=(*it)->destination;
		if (s==dest) continue;
		pair<int,int> nextHop=this->RoutingTable[s][dest][rand()%(RoutingTable[s][dest].size())];
		pair<int,int> preHop;
		preHop.first=s;
		this->FlowRoutingTable[preHop.first][(*it)->flowID]=nextHop;
		if (isMiniNet) 
			this->miniNetRuleUpdateFlowRules1(*it,preHop.first,nextHop.first);

		(*it)->edgesUsed2.erase(edge(s,d));
		while (nextHop.first!=dest) {
			preHop=nextHop;
			nextHop=this->RoutingTable[preHop.first][dest][rand()%RoutingTable[preHop.first][dest].size()];
			this->FlowRoutingTable[preHop.first][(*it)->flowID]=nextHop;
			if (isMiniNet) 
				this->miniNetRuleUpdateFlowRules1(*it,preHop.first,nextHop.first);
			(*it)->edgesUsed2.insert(edge(preHop.first,nextHop.first));
		}
	}
	this->flowsUsingThisEdge2[s][d].clear();
	this->flowsUsingThisEdge2[d][s].clear();
}
bool networkControlLogic2::FSOInUse(const FSOSt& f) {
	int active=this->activeSM[f.d][f.FSO];
	if (active==-1) return false;
	if (active==-2) return true;
	FSOSt ff=this->FSOGraph[f.d][f.FSO][active];
	if (this->topology[f.d][ff.d]>1)
		return false;
	if (this->flowsUsingThisEdge[f.d][ff.d].size()>0) 
		return true;
//	if (!this->graphRemainConnected(f)) return true;
	return false;
}
bool networkControlLogic2::updateRoutingTable() {
	return true;
}
void networkControlLogic2::reRouteElephentAugment(flowPtr f) {
	if (this->additionalTopology[f->source][f->destination]>0) {
		if (this->flowsUsingThisEdge[f->source][f->destination].size() <this->ratio) {

			list<edge>::iterator it;
			if (f->edgesUsed.size()>.0) return;

			edge sf;
			sf.s = f->source;
			sf.d = f->destination;
			//		this->FlowRoutingTable[f->source].erase(f->flowID);

			f->edgesUsed.clear();
			f->edgesUsed.push_front(sf);

			this->flowsUsingThisEdge[f->source][f->destination].insert(f);
			this->flowsUsingThisEdge[f->destination][f->source].insert(f);

			this->FlowRoutingTable[f->source][f->flowID].first = f->destination;
			this->FlowRoutingTable[f->source][f->flowID].second = this->RoutingTable[f->source][f->destination][0].second;;
		}
		return;
	}
}
void networkControlLogic2::routeElephentAugment(flowPtr f){
	if (f->isRouted) {
//		reRouteElephentAugment(flowPtr f);
		return;
	}
	f->isRouted=true;

	if (this->additionalTopology[f->source][f->destination]>0) {
		if (this->flowsUsingThisEdge[f->source][f->destination].size() <this->ratio ) {
			this->flowsUsingThisEdge[f->source][f->destination].insert(f);
			this->flowsUsingThisEdge[f->destination][f->source].insert(f);
			f->edgesUsed.clear();
			f->edgesUsed.push_back(edge(f->source, f->destination));

			this->FlowRoutingTable[f->source][f->flowID].first = f->destination;
			this->FlowRoutingTable[f->source][f->flowID].second = this->RoutingTable[f->source][f->destination][0].second;;
			return;
		}
	}

	int nextHop=this->RoutingTable[f->source][f->destination][0].first;
	edge ff;

	ff.s=f->source;
	ff.d=nextHop;

	f->edgesUsed2.insert(ff);

	this->flowsUsingThisEdge2[ff.s][ff.d].insert(f);
	this->flowsUsingThisEdge2[ff.d][ff.s].insert(f);

	this->FlowRoutingTable[ff.s][f->flowID].first=ff.d;
	this->FlowRoutingTable[ff.s][f->flowID].second=0;
	//Traffic Engineering Needed


	//ff.s=nextHop;
	while (nextHop!=f->destination) {
		ff.s=nextHop;	
		//checkConsistant();
		nextHop=this->RoutingTable[nextHop][f->destination][0].first;
		if (this->topology[nextHop][ff.s])
			ff.d=nextHop;
		else {		}

		this->flowsUsingThisEdge2[ff.s][ff.d].insert(f);
		this->flowsUsingThisEdge2[ff.d][ff.s].insert(f);

		this->FlowRoutingTable[ff.s][f->flowID].first=ff.d;
		this->FlowRoutingTable[ff.s][f->flowID].second=this->RoutingTable[ff.s][ff.d][0].second;
		//Traffic Engineering Needed
		f->edgesUsed2.insert(ff);

		if (this->topology[nextHop][ff.s]) break;
	}
}
void networkControlLogic2::reRouteElephent(flowPtr f) {

	if (f->isRouted) return;
	if (this->topology[f->source][f->destination]>0) {
		list<edge>::iterator it;
		/*
		for (it=f->edgesUsed.begin();it!=f->edgesUsed.end();it++) {
			this->flowsUsingThisEdge[it->s][it->d].erase(f);
			this->flowsUsingThisEdge2[it->s][it->d].insert(f);
			this->flowsUsingThisEdge[it->d][it->s].erase(f);
			this->flowsUsingThisEdge2[it->d][it->s].insert(f);
		}//*/
		edge sf;
		sf.s=f->source;
		sf.d=f->destination;
//		this->FlowRoutingTable[f->source].erase(f->flowID);
		//list<edge>::iterator it;
		//for (it=f->edgesUsed.begin();it!=f->edgesUsed.end();it++)
//			f->edgesUsed2.insert(*it);
		//f->edgesUsed2=f->edgesUsed;
		int nextHop=this->FlowRoutingTable[f->source][f->flowID].first;

		//f->edgesUsed2.erase(edge(sf.s,nextHop));
		//f->edgesUsed2.erase(edge(nextHop,sf.s));


		this->flowsUsingThisEdge2[sf.s][nextHop].erase(f);
		this->flowsUsingThisEdge2[nextHop][sf.s].erase(f);

		sf.s++;
		sf.s--;


		f->edgesUsed.push_front(sf);

		this->flowsUsingThisEdge[f->source][f->destination].insert(f);
		this->flowsUsingThisEdge[f->destination][f->source].insert(f);

		this->FlowRoutingTable[f->source][f->flowID].first=f->destination;
		this->FlowRoutingTable[f->source][f->flowID].second=this->RoutingTable[f->source][f->destination][0].second;
		if (isMiniNet) 
			this->miniNetRuleUpdateFlowRules1(f,f->source,f->destination);

		return;
	}
}
void networkControlLogic2::routeElephent(flowPtr f) {
	if (rand() % 4 == 2) {
		if (this->initTopology[f->source][f->destination]>0) {
			this->FlowRoutingTable[f->source][f->flowID].first = f->destination;
			this->FlowRoutingTable[f->source][f->flowID].first = 0;
			return;

		}
	}
	if (this->topology[f->source][f->destination]>0) {

		this->flowsUsingThisEdge[f->source][f->destination].insert(f);
		this->flowsUsingThisEdge[f->destination][f->source].insert(f);
		f->edgesUsed.clear();
		f->isRouted=true;
		f->edgesUsed.push_back(edge(f->source,f->destination));

		this->FlowRoutingTable[f->source][f->flowID].first=f->destination;
		this->FlowRoutingTable[f->source][f->flowID].second=0;
		if (isMiniNet) 
			this->miniNetRuleUpdateFlowRules1(f,f->source,f->destination);

		return;
	}

	if (f->isRouted) return;
	f->isRouted=false;
	int nextHop=this->RoutingTable[f->source][f->destination][0].first;
	edge ff;

	ff.s=f->source;
	ff.d=nextHop;
	f->edgesUsed2.insert(ff);


	this->flowsUsingThisEdge2[ff.s][ff.d].insert(f);
	this->flowsUsingThisEdge2[ff.d][ff.s].insert(f);

	this->FlowRoutingTable[ff.s][f->flowID].first=ff.d;
	this->FlowRoutingTable[ff.s][f->flowID].second=0;
	if (isMiniNet) 
		this->miniNetRuleUpdateFlowRules1(f,ff.s,ff.d);

	//Traffic Engineering Needed


	//ff.s=nextHop;
	while (nextHop!=f->destination) {
		ff.s=nextHop;	
		//checkConsistant();
		nextHop=this->RoutingTable[nextHop][f->destination][0].first;
		if (this->topology[nextHop][ff.s])
			ff.d=nextHop;

		this->flowsUsingThisEdge2[ff.s][ff.d].insert(f);
		this->flowsUsingThisEdge2[ff.d][ff.s].insert(f);
		f->edgesUsed2.insert(ff);

		this->FlowRoutingTable[ff.s][f->flowID].first=ff.d;
		this->FlowRoutingTable[ff.s][f->flowID].second=0;
		if (isMiniNet) 
			this->miniNetRuleUpdateFlowRules1(f,ff.s,ff.d);


		if (this->topology[nextHop][ff.s]) break;
	}
}
int networkControlLogic2::elephantFlowArrival(string flowID,int source, int destination,Sim_Timer time) {

	if (source==destination) return 0;
	switch(this->alg) {
		case tDBeam:
			elATopotDBeam(flowID,source,destination,time);
			break;
		case ourPriodicReconfig:
			elAourPriodicReconfig(flowID,source,destination,time);
		case cThrough:
			elATopocThrough(flowID,source,destination,time);
			break;
		case jellyFish:
			elATopoJellyfish(flowID,source,destination,time);
			break;
		case oursCongestion:
			elATopoOursCongestion(flowID,source,destination,time);
			break;
		case oursNoFlowRouting:
			elAoursNoFlowRouting(flowID,source,destination,time);
			break;
	}
	return true;	
}

int networkControlLogic2::elephantFlowEnd(string flowID,int source, int destination,Sim_Timer time) {

	if (this->alg==jellyFish) return 1;
	
	unordered_map<string,flow>::iterator ff;
	ff=this->elephentsInTheSystem.find(flowID);
	if (this->elephentsInTheSystem.count(flowID)==0)
		return 1;
	try{
		for (int i = 0; i < networkSize; i++) {
			this->FlowRoutingTable[i].erase(ff->second.flowID);
			for (int j = 0; j < networkSize; j++) {
				this->flowsUsingThisEdge[i][j].erase(std::addressof(ff->second));
				if (this->isMininet) {


				}
			}
		}
	}
	catch (...) {};
	try{
			list<edge>::iterator it;
			for (it=ff->second.edgesUsed.begin();it!=ff->second.edgesUsed.end();it++) {
				//this->flowsUsingThisEdge[it->s][it->d].erase(std::addressof(ff->second));
//				this->FlowRoutingTable[it->s].erase(flowID);
				//this->flowsUsingThisEdge[it->d][it->s].erase(std::addressof(ff->second));
				//this->FlowRoutingTable[it->d].erase(flowID);
			}
	}
	catch (...) {};
	try{
			list<edge>::iterator it;
			for (it = ff->second.waitingForActivation.begin(); it != ff->second.waitingForActivation.end(); ++it) {
				this->linksToBeActivated[it->s][it->d].flows.remove(std::addressof(ff->second));
				this->linksToBeActivated[it->d][it->s].flows.remove(std::addressof(ff->second));
			}
	}
	catch (...) {};
	try{
			set<edge>::iterator it;
			for (it=ff->second.edgesUsed2.begin();it!=ff->second.edgesUsed2.end();it++) {
				this->flowsUsingThisEdge2[it->s][it->d].erase(std::addressof(ff->second));
				int ss=this->flowsUsingThisEdge2[it->s][it->d].count(std::addressof(ff->second));
//				this->FlowRoutingTable[it->s].erase(flowID);
				this->flowsUsingThisEdge2[it->d][it->s].erase(std::addressof(ff->second));
				ss=this->flowsUsingThisEdge2[it->d][it->s].count(std::addressof(ff->second));
//				this->FlowRoutingTable[it->d].erase(flowID);
			}
	try{
	} catch(...) {};
		ff->second.edgesUsed.clear();
		ff->second.edgesUsed2.clear();
		this->elephentsInTheSystem.erase(flowID);
	} catch(...) {};
	currentTime=time;
	return 1;
}
void networkControlLogic2::updateRoutingAddLinkCthrough(int s,int d) {
}
void networkControlLogic2::updateRoutingAddLinktDbeam(int s,int d) {
}
void networkControlLogic2::addLink(const FSOSt& f,flowPtr fl) {

	FSOSt ff=this->FSOGraph[f.d][f.FSO][f.SM];
	bool ifretuen=false;

	int active1=this->activeSM[f.d][f.FSO];
	int active2=this->activeSM[ff.d][ff.FSO];
	assert(active1!=-2);
	assert(active2!=-2);

	if (active1!=-1)
		deleteFSOLink(f);
	if (active2!=-1) 
		deleteFSOLink(ff);
	
	this->activeSM[f.d][f.FSO]=-2;
	this->activeSM[ff.d][ff.FSO]=-2;


	this->linksToBeActivated[f.d][ff.d].t=SM_ACTINATION_TIME+currentTime;
	this->linksToBeActivated[f.d][ff.d].FSOs.push_back(ff);
	this->linksToBeActivated[f.d][ff.d].inProcess=true;
	this->linksToBeActivated[f.d][ff.d].flows.clear();
	this->linksToBeActivated[f.d][ff.d].flows.push_back(fl);
	fl->waitingForActivation.push_back(edge(f.d, ff.d));

	this->linksToBeActivated[ff.d][f.d].t=SM_ACTINATION_TIME+currentTime;
	this->linksToBeActivated[ff.d][f.d].FSOs.push_back(f);
	this->linksToBeActivated[ff.d][f.d].inProcess=true;
	this->linksToBeActivated[ff.d][f.d].flows.clear();
	this->linksToBeActivated[ff.d][f.d].flows.push_back(fl);
	


	timeEvent t;
	switch (this->alg) {
		case cThrough:
			t.t=CTHROUGH_ACTINATION_TIME+currentTime;
			break;
		case tDBeam:
			t.t=TDBEAM_ACTINATION_TIME+currentTime;
			break;
		default:
			t.t=SM_ACTINATION_TIME+currentTime;
	}
	t.s=f.d;
	t.d=ff.d;
	this->nextsCall.push_back(t);


#ifdef CheckConsistancyMacro
	checkConsistant();
#endif
}
void networkControlLogic2::addLinktDBeam(flowPtr fl) {

	this->totalAugmentLinks++;
	this->activateLinks[fl->source]++;
	this->activateLinks[fl->destination]++;

	this->linksToBeActivated[fl->source][fl->destination].t=TDBEAM_ACTINATION_TIME+currentTime;
	this->linksToBeActivated[fl->source][fl->destination].inProcess=true;
	this->linksToBeActivated[fl->source][fl->destination].flows.clear();
	this->linksToBeActivated[fl->source][fl->destination].flows.push_back(fl);
	fl->waitingForActivation.push_back(edge(fl->source, fl->destination));

	this->linksToBeActivated[fl->destination][fl->source].t=TDBEAM_ACTINATION_TIME+currentTime;
	this->linksToBeActivated[fl->destination][fl->source].inProcess=true;
	this->linksToBeActivated[fl->destination][fl->source].flows.clear();
	this->linksToBeActivated[fl->destination][fl->source].flows.push_back(fl);
	
	timeEvent t;
	t.t=TDBEAM_ACTINATION_TIME+currentTime;
	t.s=fl->source;
	t.d=fl->destination;
	this->nextsCall.push_back(t);
}
void networkControlLogic2::addLinkCthrough(flowPtr fl) {
	this->activateLinks[fl->source]++;
	this->activateLinks[fl->destination]++;

	this->totalAugmentLinks++;

	this->linksToBeActivated[fl->source][fl->destination].t=CTHROUGH_ACTINATION_TIME+currentTime;
	this->linksToBeActivated[fl->source][fl->destination].inProcess=true;
	this->linksToBeActivated[fl->source][fl->destination].flows.clear();
	this->linksToBeActivated[fl->source][fl->destination].flows.push_back(fl);
	fl->waitingForActivation.push_back(edge(fl->source, fl->destination));


	this->linksToBeActivated[fl->destination][fl->source].t=CTHROUGH_ACTINATION_TIME+currentTime;
	this->linksToBeActivated[fl->destination][fl->source].inProcess=true;
	this->linksToBeActivated[fl->destination][fl->source].flows.clear();
	this->linksToBeActivated[fl->destination][fl->source].flows.push_back(fl);

	timeEvent t;
	t.t=CTHROUGH_ACTINATION_TIME+currentTime;
	t.s=fl->source;
	t.d=fl->destination;
	this->nextsCall.push_back(t);
}
void networkControlLogic2::activateLinkcThrough(int s,int d) {
	if (this->additionalTopology[s][d]>0) return;
	augEdges[s].push_back(d);
	augEdges[d].push_back(s);

	this->additionalTopology[s][d]++;
	this->additionalTopology[d][s]++;

	this->linksToBeActivated[s][d].inProcess=false;
	this->linksToBeActivated[d][s].inProcess=false;
	
	this->RoutingTable[s][d].resize(1);
	this->RoutingTable[s][d][0].first=d;
	this->RoutingTable[s][d][0].second=this->initTopology[s][d];

	this->RoutingTable[d][s].resize(1);
	this->RoutingTable[d][s][0].first=s;
	this->RoutingTable[d][s][0].second=this->initTopology[d][s];
	//*/

	list<flowPtr>::iterator it;
	for (it=this->linksToBeActivated[s][d].flows.begin();it!=this->linksToBeActivated[s][d].flows.end();it++) {
		flowPtr f=*it;
		reRouteElephentAugment(f);
	}
	this->linksToBeActivated[s][d].flows.clear();
	//updateRoutingAddLinktDbeam(s,d);
	updateRoutingAddLinkCthrough(s,d);
}
void networkControlLogic2::activateLinktDBeam(int s,int d) {
	if (this->additionalTopology[s][d]>0) return;
	augEdges[s].push_back(d);
	augEdges[d].push_back(s);

	this->additionalTopology[s][d]++;
	this->additionalTopology[d][s]++;
	this->linksToBeActivated[s][d].inProcess=false;
	this->linksToBeActivated[d][s].inProcess=false;
	
	this->RoutingTable[s][d].resize(1);
	this->RoutingTable[s][d][0].first=d;
	this->RoutingTable[s][d][0].second=this->initTopology[s][d];

	this->RoutingTable[d][s].resize(1);
	this->RoutingTable[d][s][0].first=s;
	this->RoutingTable[d][s][0].second=this->initTopology[d][s];


	list<flowPtr>::iterator it;
	for (it=this->linksToBeActivated[s][d].flows.begin();it!=this->linksToBeActivated[s][d].flows.end();it++) {
		flowPtr f=*it;
		reRouteElephentAugment(f);
	}
	this->linksToBeActivated[s][d].flows.clear();
	updateRoutingAddLinktDbeam(s,d);
}
void networkControlLogic2::activateLink(timeEvent t) {
	switch(this->alg) {
		case cThrough:
			this->activateLinkcThrough(t.s,t.d);
			break;
		case tDBeam:
			this->activateLinktDBeam(t.s,t.d);
			break;
		default:
			activateLink(t.s,t.d);
	}
}
void networkControlLogic2::activateLink(int s,int d) {

	this->topology[s][d]++;
	this->topology[d][s]++;

	this->linksToBeActivated[s][d].inProcess=false;
	this->linksToBeActivated[d][s].inProcess=false;

	FSOSt f=this->linksToBeActivated[d][s].FSOs.front();
	FSOSt ff=this->linksToBeActivated[s][d].FSOs.front();

	list<flowPtr>::iterator it;

	this->activeSM[f.d][f.FSO]=f.SM;
	this->activeSM[ff.d][ff.FSO]=ff.SM;


	for (it=this->linksToBeActivated[s][d].flows.begin();it!=this->linksToBeActivated[s][d].flows.end();it++) {
		flowPtr f=*it;
		reRouteElephent(f);
	}
	this->linksToBeActivated[s][d].FSOs.clear();
	this->linksToBeActivated[d][s].FSOs.clear();

	this->linksToBeActivated[s][d].flows.clear();
	this->linksToBeActivated[d][s].flows.clear();
	updateRoutingAddLink(s,d);
}


void networkControlLogic2::DeleteOpenTDBeam(int f) {
	if (this->activateLinks[f]<TDBEAM_INDIVISUAL_TRESHOLD) 
		return;
	list<int>::iterator it=this->augEdges[f].begin();
	int sss=0;
	while (it!=this->augEdges[f].end()) {
		if (this->linksToBeActivated[f][*it].inProcess) {
			it++;
			continue;
		}
		if (this->flowsUsingThisEdge[f][*it].size() == 0) {
			this->augEdges[*it].remove(f);
			this->additionalTopology[f][*it]--;
			this->additionalTopology[*it][f]--;
			//this->processRoutesSecondaryPackets(*it,f);
			this->activateLinks[f]--;
			this->activateLinks[*it]--;
			this->totalAugmentLinks--;
//			this->RoutingTable[f][*it]=this->RoutingTable2[f][*it];
//			this->RoutingTable[*it][f]=this->RoutingTable2[*it][f];
			it=this->augEdges[f].erase(it);
		} else it++;
	}
}
bool networkControlLogic2::CheckOpenTDBeam(int f) {
	if (this->activateLinks[f]<TDBEAM_INDIVISUAL_TRESHOLD) 
		return true;
	list<int>::iterator it;
	int sss=0;
	for (it=this->augEdges[f].begin();it!=this->augEdges[f].end();it++) {
		if (this->linksToBeActivated[f][*it].inProcess)
			continue;
		if (this->flowsUsingThisEdge[f][*it].size()==0)
			sss++;
	}
	int canBeChanged=this->activateLinks[f]-sss;
	if (canBeChanged<TDBEAM_INDIVISUAL_TRESHOLD) 
		return true;
	return false;
}
void networkControlLogic2::DeleteOpencThrough(int f) {
	if (this->activateLinks[f]<CTHROUGH_INDIVISUAL_TRESHOLD) 
		return;
	list<int>::iterator it=this->augEdges[f].begin();
	int sss=0;
	while (it!=this->augEdges[f].end()) {
		if (this->linksToBeActivated[f][*it].inProcess) {
			it++;
			continue;
		}
		if (this->flowsUsingThisEdge[f][*it].size() == 0) {
			this->augEdges[*it].remove(f);
			this->additionalTopology[f][*it]--;
			this->additionalTopology[*it][f]--;
			//this->processRoutesSecondaryPackets(*it,f);
			this->activateLinks[f]--;
			this->activateLinks[*it]--;
			this->totalAugmentLinks--;
//			this->RoutingTable[f][*it]=this->RoutingTable2[f][*it];
//			this->RoutingTable[*it][f]=this->RoutingTable2[*it][f];
			it=this->augEdges[f].erase(it);
		} else it++;
	}
}
bool networkControlLogic2::CheckOpencThrough(int f) {
	if (this->activateLinks[f]<CTHROUGH_INDIVISUAL_TRESHOLD) 
		return true;
	list<int>::iterator it;
	int sss=0;
	for (it=this->augEdges[f].begin();it!=this->augEdges[f].end();it++) {
		if (this->linksToBeActivated[f][*it].inProcess)
			continue;
		if (this->flowsUsingThisEdge[f][*it].size()==0)
			sss++;
	}
	int canBeChanged=this->activateLinks[f]-sss;
	if (canBeChanged<CTHROUGH_INDIVISUAL_TRESHOLD) 
		return true;
	return false;
}
























/*
bool networkControlLogic2::linkInUse(FSOSt f) {
	FSOSt ff=this->FSOGraph[f.d][f.FSO][f.SM];
	if (this->flowsUsingThisEdge[f.d][ff.d].size()>0) {
		if (this->topology[f.d][ff.d]>1)
			return false;
		else return true;
	} else 
	if (linksToBeActivated[f.d][ff.d].inProcess){
		for (list<FSOSt>::iterator i=linksToBeActivated[f.d][ff.d].FSOs.begin(); i!=linksToBeActivated[f.d][ff.d].FSOs.end();i++) {
			if (
					((*i)==ff) || 
					((*i)==f)
				)  {
					return true;
			}
		}
	}
	return false;
}
//*/
