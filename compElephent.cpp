#pragma warning(disable:4503)
#pragma warning(disable:4018)

#include "navidConstants.h"
#include "networkControlLogic2.h"

bool networkControlLogic2::processNextElephentNoChange(flowPtr g) {
	routeElephent(g);
	return false;
}
bool networkControlLogic2::processNextcThrough(flowPtr f){
	bool first=false;
	bool second=false;

	if (this->activateLinks[f->source]<CTHROUGH_INDIVISUAL_TRESHOLD ) 
		first=true;
	else first=CheckOpencThrough(f->source);
	if (this->activateLinks[f->destination]<CTHROUGH_INDIVISUAL_TRESHOLD ) 
		second=true;
	else second=CheckOpencThrough(f->destination);

	if (first && second){
		if (this->activateLinks[f->source]<CTHROUGH_INDIVISUAL_TRESHOLD ) 
			first=true;
		else DeleteOpencThrough(f->source);
		if (this->activateLinks[f->destination]<CTHROUGH_INDIVISUAL_TRESHOLD ) 
			second=true;
		else DeleteOpencThrough(f->destination);
			this->addLinkCthrough(f);
			//routeElephent(f);
			return false;
	}

	return true;
}
bool networkControlLogic2::processNexttDBeam(flowPtr f) {
	bool first=false;
	bool second=false;
	if (abs(f->source-f->destination)<(this->networkSize/TDBEAM_TRESHOLD)) {
		if (totalAugmentLinks<(TDBEAM_NET_TRESHOLD*(double)this->networkSize)) {
			if (this->activateLinks[f->source]<TDBEAM_INDIVISUAL_TRESHOLD) 
				first=true;
			else first=CheckOpenTDBeam(f->source);
			if (this->activateLinks[f->destination]<TDBEAM_INDIVISUAL_TRESHOLD) 
				second=true;
			else second=CheckOpenTDBeam(f->destination);

			if (first && second){
				if (this->activateLinks[f->source]<TDBEAM_INDIVISUAL_TRESHOLD) 
					first=true;
				else DeleteOpenTDBeam(f->source);
				if (this->activateLinks[f->destination]<TDBEAM_INDIVISUAL_TRESHOLD) 
					second=true;
				else DeleteOpenTDBeam(f->destination);

					this->addLinktDBeam(f);
					//routeElephent(f);
					return false;
			}
		}
	}
	return true;
}
void networkControlLogic2::elATopoJellyfish(string flowID,int source, int destination,Sim_Timer time) {
	currentTime=time;
	flow f;
	f.flID=++(this->flID);
	f.flowID=flowID;
	f.source=source;
	f.destination=destination;
	pair<unordered_map<string,flow>::iterator ,bool> ret;
	ret=elephentsInTheSystem.insert(std::pair<string,flow>(f.flowID,f));
	this->routeElephentAugment(std::addressof(ret.first->second));
	return;
}
void networkControlLogic2::elATopocThrough(string flowID,int source, int destination,Sim_Timer time) {
	currentTime=time;
	flow f;
	f.flID=++(this->flID);
	f.flowID=flowID;
	f.source=source;
	f.destination=destination;

	pair<unordered_map<string,flow>::iterator ,bool> ret;
	ret=elephentsInTheSystem.insert(std::pair<string,flow>(f.flowID,f));
	this->routeElephentAugment(std::addressof(ret.first->second));

	this->unprocessesFlows.push_back(std::addressof(ret.first->second));
	this->computTopo(time);
	return;
}
void networkControlLogic2::elATopotDBeam(string flowID,int source, int destination,Sim_Timer time) {
	currentTime=time;
	flow f;
	f.flowID=flowID;
	f.flID=++(this->flID);
	f.source=source;
	f.destination=destination;

	pair<unordered_map<string,flow>::iterator ,bool> ret;
	ret=elephentsInTheSystem.insert(std::pair<string,flow>(f.flowID,f));
	this->routeElephentAugment(std::addressof(ret.first->second));
	this->unprocessesFlows.push_back(std::addressof(ret.first->second));

	this->computTopo(time);
	return;
}
void networkControlLogic2::elATopoOursCongestion(string flowID,int source, int destination,Sim_Timer time) {
	currentTime=time;
	flow f;
	f.flowID=flowID;
	f.flID=++(this->flID);
	f.source=source;
	f.destination=destination;

	pair<unordered_map<string,flow>::iterator ,bool> ret;
	ret=elephentsInTheSystem.insert(std::pair<string,flow>(f.flowID,f));
	this->routeElephent(std::addressof(ret.first->second));
	this->unprocessesFlows.push_back(std::addressof(ret.first->second));
	this->computTopo(time);
	return;
}
void networkControlLogic2::elAoursNoFlowRouting(string flowID,int source, int destination,Sim_Timer time) {
	currentTime=time;
	flow f;
	f.flowID=flowID;
	f.flID=++(this->flID);
	f.source=source;
	f.destination=destination;

	pair<unordered_map<string,flow>::iterator ,bool> ret;
	ret=elephentsInTheSystem.insert(std::pair<string,flow>(f.flowID,f));
	this->routeElephent(std::addressof(ret.first->second));
	this->unprocessesFlows.push_back(std::addressof(ret.first->second));
	this->computTopo(time);
	return;
}
void networkControlLogic2::elAourPriodicReconfig(string flowID,int source, int destination,Sim_Timer time) {
	currentTime=time;
	flow f;
	f.flowID=flowID;
	f.flID=++(this->flID);
	f.source=source;
	f.destination=destination;

	pair<unordered_map<string,flow>::iterator ,bool> ret;
	ret=elephentsInTheSystem.insert(std::pair<string,flow>(f.flowID,f));
	this->routeElephent(std::addressof(ret.first->second));
	this->unprocessesFlows.push_back(std::addressof(ret.first->second));
	this->computTopo(time);
	return;
}
bool networkControlLogic2::processNextElephent(flowPtr g) {
	flow& f=*g;
	if (topology[f.source][f.destination]>0) {
		routeElephent(g);
		return false;
	} else if (this->linksToBeActivated[f.source][f.destination].inProcess) {
		this->linksToBeActivated[f.source][f.destination].flows.push_back(std::addressof(elephentsInTheSystem.find(f.flowID)->second));
		this->linksToBeActivated[f.destination][f.source].flows.push_back(std::addressof(elephentsInTheSystem.find(f.flowID)->second));
		routeElephent(g);
		return false;
	} else if (initTopology[f.source][f.destination]>0) {
		FSOSt candid1;

		static FSOSt cands[1000];
		static FSOSt isUsed[1000];
		int csize=-1;
		int attempts=0;

		candid1.d=-1;
		for (int i=0;i<this->FSONum;i++) {
			if (this->activeSM[f.source][i]==-1) {
				for (int j=0;j<this->MirrorNum;j++) {
					FSOSt ff=this->FSOGraph[f.source][i][j];
					FSOSt gg=this->FSOGraph[ff.d][ff.FSO][ff.SM];
					if ((ff.d==f.destination) && (gg.d==f.source) && (gg.FSO==i) && (gg.SM==j)) {
						if (this->activeSM[ff.d][ff.FSO]==-1) {
							this->addLink(gg,g);
							return true;
						}
						else {
							cands[++csize]=ff;
						}
					}
				}
			}
		} //end for 
		if (csize>-1) {
			while (++attempts<5) {
				int ff=rand()%(csize+1);
				if (!FSOInUse(cands[ff])) {
					FSOSt gg=this->FSOGraph[cands[ff].d][cands[ff].FSO][cands[ff].SM];
					if (!FSOInUse(gg)) {
						if (graphRemainConnected(gg) && graphRemainConnected(cands[ff])) {
							candid1=cands[ff];
							continue;
						}
					}
				}
			}
		}
		if (candid1.d==-1) {
			for (int ff=0;ff<=csize;ff++) {
				if (!FSOInUse(cands[ff])) {
					FSOSt gg=this->FSOGraph[cands[ff].d][cands[ff].FSO][cands[ff].SM];
					if (!FSOInUse(gg)) {
						if (graphRemainConnected(gg) && graphRemainConnected(cands[ff])) {
							candid1=cands[ff];
							continue;
						}
					}
					}
			}
		}
		csize=-1;
		if (candid1.d==-1) {
			for (int i=0;i<this->FSONum;i++) {
					if (this->activeSM[f.destination][i]==-1) {
						for (int j=0;j<this->MirrorNum;j++) {
							FSOSt ff=this->FSOGraph[f.destination][i][j];
							if (ff.d==f.source) {
								cands[++csize]=ff;
							}
						}
					}
			}
		}
		if (csize>-1) {
			while (++attempts<5) {
				int ff=rand()%(csize+1);
				if (!FSOInUse(cands[ff])) {
					FSOSt gg=this->FSOGraph[cands[ff].d][cands[ff].FSO][cands[ff].SM];
					if (!FSOInUse(gg)) {
						if (graphRemainConnected(gg) && graphRemainConnected(cands[ff])) {
							candid1=cands[ff];
							continue;
						}
					}
				}
			}
		}
		if (candid1.d==-1) {
			for (int ff=0;ff<=csize;ff++) {
				if (!FSOInUse(cands[ff])) {
					FSOSt gg=this->FSOGraph[cands[ff].d][cands[ff].FSO][cands[ff].SM];
					if (!FSOInUse(gg)) {
						if (graphRemainConnected(gg) && graphRemainConnected(cands[ff])) {
							candid1=cands[ff];
							continue;
						}
					}
					}
			}
		}
		if (candid1.d==-1) {
			csize=-1;
			for (int i=0;i<this->FSONum;i++) {
				for (int j=0;j<this->MirrorNum;j++) {
					FSOSt ff=this->FSOGraph[f.destination][i][j];
					FSOSt gg=this->FSOGraph[ff.d][ff.FSO][ff.SM];
					if (ff.d==f.source) 
							cands[++csize]=ff;
				}
			}
			if (csize>-1) {
				attempts=0;
				while (++attempts<7) {
					int ff=rand()%(csize+1);
					if (!FSOInUse(cands[ff])) {
						FSOSt gg=this->FSOGraph[cands[ff].d][cands[ff].FSO][cands[ff].SM];
						if (!FSOInUse(gg)) {
							if ((graphRemainConnected(gg)) && (graphRemainConnected(cands[ff]))) {
								candid1=cands[ff];
								break;
							}
						}
					}
				}
				if	(candid1.d==-1) {
					for (int ff=0;ff<=csize;ff++) {
						if (!FSOInUse(cands[ff])) {
							FSOSt gg=this->FSOGraph[cands[ff].d][cands[ff].FSO][cands[ff].SM];
							if (!FSOInUse(gg)) {
								if ((graphRemainConnected(gg)) && (graphRemainConnected(cands[ff]))) {
									candid1=cands[ff];
									break;
								}
							}
						}
					}
				}
			}
		} 

		if (candid1.d==-1) {
			routeElephent(g);
			return false;
		} else {
			FSOSt gg=this->FSOGraph[candid1.d][candid1.FSO][candid1.SM];
			addLink(gg,g);
			routeElephent(g);
			return true;
		}
	} 
	routeElephent(g);
	return false;
}








