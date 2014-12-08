#ifdef _MSC_VER
#define snprintf _snprintf
#endif
#pragma warning(disable:4503)
#pragma warning(disable:4018)

#include "networkControlLogic2.h"
#include "GenerateFattree.h"
#include <stdlib.h>

/* Added for fs */
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
/***************/


#define DEBUG


bool networkControlLogic2::checkConsistant() {
	//return true;
	map<int, map<int, vector<std::pair<int,int> > > >::iterator it;
	vector<vector<int> > fff(networkSize,vector<int>(networkSize,0));
//	if ()
//	cout<<"routing table size is "<<this->RoutingTable.size()<<endl;

	for (int i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
				int k=this->activeSM[i][j];
				if (k>-1) {
					FSOSt f;
					f=this->FSOGraph[i][j][k];
					if (activeSM[f.d][f.FSO]!=f.SM)
						cout<<"fucck7";
					fff[i][f.d]++;
					fff[f.d][i]++;
				}
		}
	}
	for (int i=0;i<this->networkSize;i++) {
		for (int j=0;j<this->networkSize;j++) {
				if (!(topology[i][j]*2==fff[i][j])) {
					cout<<"fucck4";
				}
				if (!(topology[j][i]*2==fff[i][j])) {
					cout<<"fucck5";
				}
				if (fff[j][i]!=fff[i][j]) {
					cout<<"fucck6";
				}
		}
	}//*/


	for (int i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
			for (int f=0;f<RoutingTable[i][j].size();f++) {
				int k=RoutingTable[i][j][f].first;
				int k2=RoutingTable[i][j][f].second;
				if (i!=k) {
					if (!(k2<this->topology[i][k])) {
						cout<<"fucck3";
					}
					if (!(this->topology[i][k]>0)) {
						cout<<"fucck2";
					}
					if (this->topology[k][k2]!=this->topology[k2][k]) {
						cout<<"fucck1";
					}
				}
			}
		}
	}
	
	return true;
}
void randperm(int n, vector<int>& perm)
{
	perm.resize(n);
	int i, j, t;
	for(i=0; i<n; i++)
		perm[i] = i;
	for(i=0; i<n; i++) {
		j = rand()%(n-i)+i;
		t = perm[j];
		perm[j] = perm[i];
		perm[i] = t;
	}
}
/*
trafficAlgorithm int2trafficAlgorithm(int n)
{
  switch( n )
  {
    case 0 :  return tDBeam;
    case 1 :  return cThrough;
    case 2 :  return oursCongestion;
    case 3 :  return oursNoFlowRouting;
  }
}

int trafficAlgorithm2int(trafficAlgorithm e)
{
  switch( e )
  {
    case tDBeam :  return 0;
    case cThrough :  return 1;
    case cThrough :  return 2;
    case oursNoFlowRouting :  return 3;
  }
}
*/
void networkControlLogic2::initcThrouh(){

	this->MirrorNum=1;
	this->networkSize=this->networkSize*4;
	this->initateMemory();
	priodicTime=PRIODICTIME_CTHROUGH;
	randomGraph a;
	this->topology=a.randomJellyGraph(this->networkSize/4,this->FSONum);
	this->initTopology=this->topology;
	this->augNetworkSize=networkSize;
	networkSize=networkSize/4;
	vector<int> perms;
	randperm(this->networkSize,perms);
	this->initAdditionalTopology.resize(this->networkSize);
	for (int i=0;i<this->networkSize;i++) {
		this->initAdditionalTopology[i].resize(this->networkSize);
		this->additionalTopology[i].resize(this->networkSize);
		for (int j=0;j<this->networkSize;j++) {
			this->additionalTopology[i][j]=0;
			this->initAdditionalTopology[i][j]=1;
		}
	}
	for (int i=0;i<this->networkSize;i=i+2) {
		this->additionalTopology[perms[i]][perms[i+1]]=1;
		this->additionalTopology[perms[i+1]][perms[i]]=1;
	}//*/

	networkSize=networkSize*4;
	BFSOneNodeUpdateRoutesUpdateAllAugment();
}
void networkControlLogic2::initJellyFish() {
	this->MirrorNum=1;
	this->networkSize=this->networkSize*4;
	this->initateMemory();
	randomGraph a;
	this->augNetworkSize=networkSize;
	this->topology=a.randomJellyGraph(this->networkSize/4,this->FSONum);
	this->initTopology=this->topology;
	networkSize=networkSize/4;
	BFSOneNodeUpdateRoutesUpdateAllAugment();
}


void networkControlLogic2::initFattree() {
	this->MirrorNum = 1;
	//this->networkSize = this->networkSize * 4;
	this->initateMemory();
	randomGraph a;
	this->augNetworkSize = networkSize;
	this->topology = GenerateFattree(this->networkSize);
	this->networkSize = topology.size();
	this->initTopology = this->topology;
	BFSOneNodeUpdateRoutesUpdateAllAugment();
}



void networkControlLogic2::inittDbeam() {
	this->MirrorNum=1;
	this->networkSize=this->networkSize*4;
	this->initateMemory();
	randomGraph a;
	this->augNetworkSize=networkSize;

	this->topology=a.randomJellyGraph(this->networkSize/4,this->FSONum);
	this->initTopology=this->topology;
	networkSize=networkSize/4;
	
//	this->initAdditionalTopology=vector<vector<int> >(this->networkSize,vector<int>(this->networkSize,1));
	this->initAdditionalTopology.resize(this->networkSize);
	for (int i=0;i<this->networkSize;i++) {
		this->initAdditionalTopology[i].resize(this->networkSize);
		this->additionalTopology[i].resize(this->networkSize);
		//RoutingTable[i].resize(this->networkSize);
		for (int j=0;j<this->networkSize;j++) {
			this->additionalTopology[i][j]=0;
			this->initAdditionalTopology[i][j]=1;
		}
	}
	for (int i=0;i<this->networkSize;i++) {
		int k=rand()%this->networkSize;
		while ((i!=k) && (this->additionalTopology[i][k]!=0) )
			k=rand()%this->networkSize;
		this->additionalTopology[i][k]=1;
		this->additionalTopology[k][i]=1;
	}
	networkSize=networkSize*4;
	BFSOneNodeUpdateRoutesUpdateAllAugment();
}
bool networkControlLogic2::graphRemainConnected(const FSOSt& f) {
	int active=this->activeSM[f.d][f.FSO];
	if (active<0) return true;
	FSOSt ff=this->FSOGraph[f.d][f.FSO][active];
	return this->checkRemainConnected(f.d,ff.d);
}
void networkControlLogic2::initateMemory() {
	doRSM(networkSize, FSONum, MirrorNum);
	this->currentHop=vector<vector<int> > (networkSize,vector<int>(networkSize,-1));
	this->visitedLeft.resize(this->networkSize);
	this->visitedRight.resize(this->networkSize);
	distances.resize(networkSize);
	numberOfRoutes.resize(networkSize);
	topology.resize(this->networkSize);
	checked1.resize(networkSize);
	checked2.resize(networkSize);
	alternateBFS2.resize(networkSize);
	alternateBFS1.resize(networkSize);
	initTopology.resize(networkSize);
	trafficVolume.resize(networkSize);
	trafficVolumeInTransit.resize(networkSize);
	elephentsVolume.resize(networkSize);
	elephentsNumInTransit.resize(networkSize);	
	elephentsVolumeInTransit.resize(networkSize);
	elephentsNum.resize(networkSize);
	linksToBeActivated.resize(networkSize);
	additionalTopology.resize(networkSize);
	whichChanged.resize(networkSize);
	activateLinks.resize(networkSize);
	initAdditionalTopology.resize(networkSize);
	flowsUsingThisEdge.resize(networkSize);
	flowsUsingThisEdge2.resize(networkSize);
	nextsCall.resize(0);
	RoutingTable.resize(this->networkSize);
	RoutingTable2.resize(this->networkSize);
	if (isMiniNet)
		this->routingHops=vector<vector<vector<bool> > >(networkSize,vector<vector<bool> >(networkSize, vector<bool>(networkSize,false)));
	for (int i=0;i<this->networkSize;i++) {
		this->visitedLeft[i]=lastRun;
		this->visitedRight[i]=lastRun;
		flowsUsingThisEdge2[i].resize(networkSize);
		RoutingTable[i].resize(this->networkSize);
		RoutingTable2[i].resize(this->networkSize);
		initTopology[i].resize(networkSize);
		linksToBeActivated[i].resize(networkSize);
		this->topology[i].resize(this->networkSize);
		additionalTopology[i].resize(networkSize);
		initAdditionalTopology[i].resize(networkSize);
		flowsUsingThisEdge[i].resize(networkSize);
		activateLinks[i]=0;
		whichChanged[i].resize(networkSize);
		distances[i].resize(networkSize);
		numberOfRoutes[i].resize(networkSize);
		trafficVolume[i].resize(networkSize);
		trafficVolumeInTransit[i].resize(networkSize);
		elephentsVolume[i].resize(networkSize);
		elephentsVolumeInTransit[i].resize(networkSize);
		elephentsNumInTransit[i].resize(networkSize);	
		elephentsNum[i].resize(networkSize);
		for (int j = 0; j<this->networkSize; j++) {
			whichChanged[i][j]=-1;
			this->topology[i][j]=0;
			this->initTopology[i][j]=0;
			this->linksToBeActivated[i][j].inProcess=false;
		}
	}
	for (int i=0;i<this->networkSize;i++)
		for (int j=0;j<this->networkSize;j++)
			this->RoutingTable[i][j].reserve(MAX_NEXT_HOP);
}
void networkControlLogic2::BFSOneNodeUpdateRoutesUpdateAll() {

	for (int i=0;i<this->networkSize;i++)
		this->BFSOneNodeUpdateRoutes(i);
}
void networkControlLogic2::BFSOneNodeUpdateRoutesUpdateAllAugment() {

	for (int i=0;i<this->augNetworkSize;i++)
		this->BFSOneNodeUpdateRoutesAugment(i);
}
void networkControlLogic2::BFSOneNodeUpdateRoutes(int s) {
	switch (this->alg) {
		case cThrough:
			BFSOneNodeUpdateRoutescThrough(s);
			return;
			break;
		case tDBeam:
			BFSOneNodeUpdateRoutestDBeam(s);
			return;
			break;
	}
	
	static vector<int> parent;
	static vector<vector<int> > par;
	static vector<vector<edge> > par2;
	static vector<int> psize;
	static vector<int> psize2;
	static vector<int> p2size;
	static vector<bool> curHop;
	static bool isInit=false;
	if (isMiniNet)
		curHop=vector<bool>(networkSize,false);
	

	if (!isInit) {
		isInit=true;
		parent.resize(this->networkSize);
		par.resize(this->networkSize);
		psize.resize(this->networkSize);
		psize2.resize(this->networkSize);
		p2size.resize(this->networkSize);
		par2.resize(this->networkSize);
		for (int i=0;i<this->networkSize;i++) {
			par[i].resize(this->maxPath);
			par2[i].resize(this->networkSize);
		}
	}

	for (int i=0;i<this->networkSize;i++) {
		parent[i]=-1;
		psize[i]=-1;
		psize2[i]=-1;
		p2size[i]=-1;
		par[i][0]=-1;
	}
	parent[s]=0;

	list<int> nodes;
	nodes.push_front(s);
	this->distances[s][s]=0;
	this->numberOfRoutes[s][s]=0;

	if (isMiniNet)
		curHop[s]=false;


	while (nodes.size()>0) {
		int n=nodes.front();
		nodes.pop_front();
		
		for (int i=0;i<this->FSONum;i++) {
			if (this->activeSM[n][i]>-1) {
				int fd=this->FSOGraph[n][i][this->activeSM[n][i]].d;
				if (parent[fd]==-1) {
					parent[fd]=parent[n]+1;
					this->numberOfRoutes[s][fd]=1;
					this->distances[s][fd]=parent[fd];
					if (isMiniNet)
						if (currentHop[s][fd]==n)
							curHop[fd]=true;
					nodes.push_back(fd);
				}
				if (parent[fd]==parent[n]+1){
					this->numberOfRoutes[s][fd]=1;
					if (psize[fd]<this->maxPath-1) {
						if (parent[fd]<=2) {
							par[fd][++psize[fd]]=n;
							par2[fd][psize[fd]].s=fd;
							par2[fd][psize[fd]].d=n;
							if (isMiniNet)
								if (currentHop[s][fd]==n)
									curHop[fd]=true;
						}
						else {
							par[fd][++psize[fd]]=par[n][rand()%(psize[n]+1)];
							par2[fd][psize[fd]].d=n;
							if (isMiniNet)
								if (curHop[n]==true)
									curHop[fd]=true;
						}
						psize2[fd]++;
					} else 
					if (psize[fd]<this->maxPath-1) {
						if ((rand()%psize2[fd])==0) {
							psize[fd]++;
								if (parent[fd]<=2)  {
									par[fd][rand()%maxPath]=n;
									par2[fd][psize[fd]].s=fd;
									par2[fd][psize[fd]].d=n;
									if (isMiniNet)
										if (curHop[n]==true)
											curHop[fd]=true;
								}
								else {
									par[fd][rand()%maxPath]=par[n][rand()%(psize[n]+1)];
									par2[fd][psize[fd]].s=fd;
									par2[fd][psize[fd]].d=n;
									if (isMiniNet)
										if (curHop[n]==true)
											curHop[fd]=true;
								}
						}
					}
				}
			}
		}
	}

	for (int i=0;i<s;i++) {
		if (this->topology[s][i]>0) {
			this->RoutingTable[s][i].resize(1);
			this->RoutingTable[s][i][0].first=i;
			this->RoutingTable[s][i][0].second=0;
			updateFlow++;
			continue;
		}
		this->RoutingTable[s][i].resize(psize[i]+1);
		for (int j=0;j<=psize[i];j++) {
			this->RoutingTable[s][i][j].first=par[i][j];
			this->RoutingTable[s][i][j].second=0;
			updateFlow++;
		}
		for (int j=0;j<=p2size[i];j++) {
			edge ff;
			this->beingUsed[s][i].push_back(ff);
		}

	}
	this->RoutingTable[s][s].resize(0);
	for (int i=s+1;i<this->networkSize;i++) {
		if (this->topology[s][i]>0) {
			this->RoutingTable[s][i].resize(1);
			this->RoutingTable[s][i][0].first=i;
			this->RoutingTable[s][i][0].second=0;
			updateFlow++;
			continue;
		}
		this->RoutingTable[s][i].resize(psize[i]+1);
		for (int j=0;j<=psize[i];j++) {
			if (s==par[i][j]) {
				this->RoutingTable[s][i][j].first=i;
				this->RoutingTable[s][i][j].second=0;
				continue;					
			}
			this->RoutingTable[s][i][j].first=par[i][j];
			this->RoutingTable[s][i][j].second=0;

			updateFlow++;
		}
	}
	if (isMiniNet) {
		for (int i=0;i<s;i++) {
			if (!curHop[i]) {
				this->currentHop[s][i]=this->RoutingTable[s][i][0].first;
				this->miniNetRuleUpdate1(s,i,this->RoutingTable[s][i][0].first);
			}
		}
	}

}
bool networkControlLogic2::isConnected() {
	vector<bool> visited;
	visited.insert(visited.begin(),130,false);
	list<int> nodes;
	nodes.push_front(0);
	visited[0]=0;
//	visited[1]=1;
	while (nodes.size()>0) {
		int n=nodes.front();
		nodes.pop_front();
		for (int i=0;i<this->FSONum;i++) {
			if (this->activeSM[n][i]>-1) {
				FSOSt f=this->FSOGraph[n][i][this->activeSM[n][i]];
				if (!visited[f.d]) {
					visited[f.d]=true;
					nodes.push_back(f.d);
				}
			}
		}
	}
	for (int i=0;i<this->networkSize;i++) {
		if (!visited[i])
			return false;
	}
	return true;
}
bool networkControlLogic2::checkRemainConnected(int s, int d) {

	 if (s==d) {
		 return true;
	 }
	 if (this->topology[s][d]!=1) {
		return true;
	 }

	bool notFound=true;
	int visitedNum=0;
	list<int> visitedNodes;
	vector<bool> visited(this->networkSize,false);
	visited[s]=true;
	visitedNodes.push_back(s);

	while ((visitedNodes.size()>0)) {
		if (visitedNodes.size()>0) {
			int left=visitedNodes.front();
			visitedNodes.pop_front();
			for (int i=0;i<this->FSONum;i++) {
				if (this->activeSM[left][i]<=-1) continue;
				int tt=this->FSOGraph[left][i][this->activeSM[left][i]].d;
				if (tt==d) 
					return true;
				else if (!visited[tt])
					visited[tt]=true;
			}
		}
	}
	return false;
}
void networkControlLogic2::reset() {
	this->initilize(this->networkSize,this->FSONum,this->MirrorNum,this->alg);
}

/*  Added for fs */
int vectorSizeCalc(vector<std::pair<int,int>> v)
{
	return v.size();
}

/*********************/

void networkControlLogic2::initilize(int networkSize,int FSONum,int MirrorNumber,trafficAlgorithm algo)
{
	this->isMiniNet=false;
	if (algo == ourCombined) {
		algo = oursCongestion;
		isPriodicActive = true;
	}
	else isPriodicActive = false;
	
	flID=0;
	this->alg=algo;
	this->networkLocked=true;
	this->networkSize=networkSize;
	this->FSONum=FSONum;
	this->nextsCall.clear();
	this->nextsCall.resize(0);
	this->MirrorNum=MirrorNumber;
	this->totalAugmentLinks=0;
	switch(this->alg) {
		case tDBeam:
			inittDbeam();
			this->networkLocked=false;
			break;
		case cThrough:
			initcThrouh();
			this->networkLocked=true;
			break;
		case jellyFish:
			this->networkLocked=true;
			initJellyFish();
			break;
		case fatTree:
			this->networkLocked = true;
			initFattree();
			break;
		case oursCongestion:
		case oursNoFlowRouting:
			this->networkLocked=false;
		case ourPriodicReconfig:
			this->priodicTime=PRIODICTIME_FIRFLY;
			initateMemory();
		//	srand((unsigned int)time(NULL));
			srand((unsigned int)18369814883985);
			this->readGraph();
			this->lastRun=0;
	
	}
	if (isMiniNet) {
		for (int i=0;i<this->networkSize;i++) {
			for (int j=0;j<this->networkSize;j++) {
				this->currentHop[i][j]=this->RoutingTable[i][j][0].first;
			}
		}
	}
		

	
//	isTrafficExist=false;
}
void networkControlLogic2::initilizeAugmented(int networkSize, int FSONum, int MirrorNumber, trafficAlgorithm algo,float ratio)
{
	this->ratio = 1/ratio;
	this->isMiniNet = false;
	if (algo == ourCombined) {
		algo = oursCongestion;
		isPriodicActive = true;
	}
	else isPriodicActive = false;
	flID = 0;
	this->alg = algo;
	this->networkLocked = true;
	this->networkSize = networkSize;
	this->FSONum = FSONum;
	this->nextsCall.clear();
	this->nextsCall.resize(0);
	this->MirrorNum = MirrorNumber;
	this->totalAugmentLinks = 0;
	switch (this->alg) {
	case tDBeam:
		inittDbeam();
		this->networkLocked = false;
		break;
	case cThrough:
		initcThrouh();
		this->networkLocked = true;
		break;
	case jellyFish:
		throw "this function is only supposed to be called for 3dBeam and c-Through";
		break;
	case oursCongestion:
		throw "this function is only supposed to be called for 3dBeam and c-Through";
		break;
	case oursNoFlowRouting:
		throw "this function is only supposed to be called for 3dBeam and c-Through";
		break;
	case ourPriodicReconfig:
		throw "this function is only supposed to be called for 3dBeam and c-Through";
		break;
	}
}


void networkControlLogic2::initilizeMiniNet(int networkSize,int FSONum,int MirrorNumber,trafficAlgorithm algo)
{
	this->isMiniNet=true;
	flID=0;
	this->alg=algo;
	this->networkLocked=true;
	this->networkSize=networkSize;
	this->FSONum=FSONum;
	this->nextsCall.clear();
	this->nextsCall.resize(0);
	this->MirrorNum=MirrorNumber;
	this->totalAugmentLinks=0;
	switch(this->alg) {
		case tDBeam:
			inittDbeam();
			this->networkLocked=false;
			break;
		case cThrough:
			initcThrouh();
			this->networkLocked=true;
			break;
		case jellyFish:
			this->networkLocked=true;
			initJellyFish();
			break;
		case oursCongestion:
		case oursNoFlowRouting:
			this->networkLocked=false;
		case ourPriodicReconfig:
			this->priodicTime=PRIODICTIME_FIRFLY;
			initateMemory();
		//	srand((unsigned int)time(NULL));
			srand((unsigned int)18369814883985);
			this->readGraph();
			this->lastRun=0;
	}
	this->newMessages.reserve(1000000);
	int sizen=this->networkSize;
	Sim_Timer ss=SIMULATION_CLOCK_PER_MICRO_SECOND*1000;
	Sim_Timer sfd=0;
/*	for (int j=1;j<2;j++) {
		for (int i=0;i<2000;i++) {
			char buf[500];
			snprintf(buf,500,"f%d",j*2000+i);
			std::string s(buf);
			int h=rand()%sizen;
			int k=rand()%sizen;
			while (h==i) h=rand()%sizen;
			elephantFlowArrival(s,k,h,sfd);
			sfd+=ss;
		}
		for (int i=0;i<200;i++) {
			computTopo(sfd);
			sfd+=ss;
		}
		for (int i=0;i<2000;i++) {
			char buf[500];
			snprintf(buf,500,"f%d",j*2000+i);
			std::string s(buf);
			int h=0;
			elephantFlowEnd(s,i,h,sfd);
			sfd+=ss;
		}
	}//*/
	currentHop.resize(networkSize);
	//currentHop.resize();
	if (isMiniNet) {
		for (int i = 0; i<this->networkSize; i++) {
			//cout << i;
			this->currentHop[i].resize(networkSize);
			for (int j = 0; j<this->networkSize; j++) {
				if (i == j)
					this->currentHop[i][j] = -1;
				else
				this->currentHop[i][j] = this->RoutingTable[i][j][0].first;
				//					this->miniNetRuleUpdate1(s, i, this->RoutingTable[s][i][0].first);
			}
		}
	}
	//cout << "finished";

//	isTrafficExist=false;
}

void networkControlLogic2::initilizeFS(int networkSize,int FSONum,int MirrorNumber,trafficAlgorithm algo)
{

	this->isFS=true;
	flID=0;
	this->alg=algo;
	this->networkLocked=true;
	this->networkSize=networkSize;
	this->FSONum=FSONum;
	this->nextsCall.clear();
	this->nextsCall.resize(0);
	this->MirrorNum=MirrorNumber;
	this->totalAugmentLinks=0;
	switch(this->alg) {
		case tDBeam:
			inittDbeam();
			this->networkLocked=false;
			break;
		case cThrough:
			initcThrouh();
			this->networkLocked=true;
			break;
		case jellyFish:
			this->networkLocked=true;
			initJellyFish();
			break;
		case fatTree:
			this->networkLocked = true;
			initFattree();
			break;
		case oursCongestion:
		case oursNoFlowRouting:
			this->networkLocked=false;
		case ourPriodicReconfig:
			this->priodicTime=PRIODICTIME_FIRFLY;
			initateMemory();
		//	srand((unsigned int)time(NULL));
			srand((unsigned int)18369814883985);
			this->readGraph();
			this->lastRun=0;
	}
	this->newMessages.reserve(1000000);
	int sizen=this->networkSize;
	Sim_Timer ss=SIMULATION_CLOCK_PER_MICRO_SECOND*1000;
	Sim_Timer sfd=0;
	for (int j=1;j<2;j++) {
		for (int i=0;i<2000;i++) {
			char buf[500];
			snprintf(buf,500,"f%d",j*2000+i);
			std::string s(buf);
			int h=rand()%sizen;
			int k=rand()%sizen;
			while (h==i) h=rand()%sizen;
			elephantFlowArrival(s,k,h,sfd);
			sfd+=ss;
		}
		for (int i=0;i<200;i++) {
			computTopo(sfd);
			sfd+=ss;
		}
		for (int i=0;i<2000;i++) {
			char buf[500];
			snprintf(buf,500,"f%d",j*2000+i);
			std::string s(buf);
			int h=0;
			elephantFlowEnd(s,i,h,sfd);
			sfd+=ss;
		}
	}
	
//	isTrafficExist=false;
}


void networkControlLogic2::readGraph()
{
	doSM(networkSize, FSONum, MirrorNum);

	clock_t t1=clock();
	static char buff[500];
	snprintf(buff,500, "graph_%d_%d_%d.txt", networkSize, FSONum, MirrorNum);
	doRSM(networkSize, FSONum, MirrorNum);

	this->FSOGraph.resize(this->networkSize); //Graph in which each FSO mirror destination is marked
	this->FSOLinks.resize(networkSize);
	this->activeSM.resize(networkSize);

	ifstream ifs(buff, ifstream::in);
	int data,i;
	for (i=0;i<this->networkSize;i++) {
		this->FSOGraph[i].resize(FSONum);
		this->FSOLinks[i].resize(networkSize);
		this->activeSM[i].resize(FSONum);
		for (int j=0;j<FSONum;j++) {
			this->activeSM[i][j]=-1;
		}

	}

	for (i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
			FSOGraph[i][j].resize(MirrorNum);
			for (int k=0;k<MirrorNum;k++) {
	          ifs  >> data;
			  this->FSOGraph[i][j][k].d=data-1;
			  this->FSOGraph[i][j][k].FSO=-1;
			  if (this->FSOGraph[i][j][k].d==i)
				  cout<<"Old version of matrix codes";

			  FSOLinks[i][data-1]++;
			}
		}
	}
	clock_t t2=clock();
	cout<<(t2-t1)<<" "<<CLOCKS_PER_SEC<<endl;
	t1=clock();

	for (i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
			for (int k=0;k<MirrorNum;k++) {
				int f=this->FSOGraph[i][j][k].d;
				if (this->FSOGraph[i][j][k].FSO!=-1)
					goto loopEnd;
				for (int j1=0;j1<FSONum;j1++) {
					for (int k1=0;k1<MirrorNum;k1++) {
						if ((this->FSOGraph[f][j1][k1].d==i) &&
							(this->FSOGraph[f][j1][k1].FSO==-1)
							)
						{
							this->FSOGraph[f][j1][k1].FSO=j;
							this->FSOGraph[f][j1][k1].SM=k;

							this->FSOGraph[i][j][k].FSO=j1;
							this->FSOGraph[i][j][k].SM=k1;
							goto loopEnd;
						}
					}
				}
				loopEnd:
				int tt;
				tt=1;
			}
		}
	}

	t2=clock();
	cout<<(t2-t1)<<" "<<CLOCKS_PER_SEC<<endl;
	t1=clock();

	for (i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
			for (int k=0;k<MirrorNum;k++) {
				FSOSt f,g;
				f=this->FSOGraph[i][j][k];
				g=this->FSOGraph[f.d][f.FSO][f.SM];
				if (
					(this->FSOGraph[f.d][f.FSO][f.SM].d==i) &&
					(this->FSOGraph[f.d][f.FSO][f.SM].FSO==j) &&
					(this->FSOGraph[f.d][f.FSO][f.SM].SM==k)
					)
				{
					this->initTopology[i][f.d]++;
					this->initTopology[f.d][i]++;
				} else {
					cout<<"Error";
				}
				if (this->FSOGraph[f.d][f.FSO][f.SM].FSO==-1)
					cout<<"Error in reading file, uneven matrix";
			}
		}
	}
	ifs.close();
	t2=clock();
	//cout<<(t2-t1)<<" "<<CLOCKS_PER_SEC<<endl;
	constructLinks();
	BFSOneNodeUpdateRoutesUpdateAll();

	//this->checkConsistant();
	//cout<<"success";

}
bool networkControlLogic2::checkConsist(void) {
		for (int i=0;i<this->networkSize;i++) {
			for (int j=0;j<FSONum;j++) {
					int k=this->activeSM[i][j];
					if (k==-1) continue;
					FSOSt f;
					f=this->FSOGraph[i][j][k];
//					this->topology[i][f.d]++;
	//				this->topology[f.d][i]++;
					if (this->FSOGraph[f.d][f.FSO][f.SM].d!=i) 
						return false;	
					if (this->FSOGraph[f.d][f.FSO][f.SM].FSO!=j) 
						return false;
					if (this->FSOGraph[f.d][f.FSO][f.SM].SM!=k) 
						return false;
			}
		}
		return true;
}
void networkControlLogic2::constructLinks(void)
{
	//v1 = rand() % 100;         // v1 in the range 0 to 99
	int ff=0;
	for (int i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
			int k = rand() % this->MirrorNum;
			if (this->activeSM[i][j]==-1) {
				FSOSt f;
				f=this->FSOGraph[i][j][k];
				bool isFound=true;
				if (this->activeSM[f.d][f.FSO]!=-1) {
					isFound=false;
					/*
					for (int j1=0;j1<this->MirrorNum;j1++) {
						f=this->FSOGraph[i][j][j1];
						if (this->activeSM[f.d][f.FSO]==-1) {
							k=j1;
							isFound=true;
							break;
						}
					}
					//*/
				}
				if (isFound==false) {
				} else{
						if (this->activeSM[f.d][f.FSO]>0)
							cout<<"trouble2";

					this->activeSM[f.d][f.FSO]=f.SM;
					this->activeSM[i][j]=k;
					ff++;
					assert(this->FSOGraph[f.d][f.FSO][f.SM].d==i);
					assert(this->FSOGraph[f.d][f.FSO][f.SM].FSO==j);
					assert(this->FSOGraph[f.d][f.FSO][f.SM].SM==k);
					
#ifdef CheckConsistMacro
					if (!checkConsist())
						cout<<"ss";
#endif
				}

				int count=0;
				for (int i=0;i<this->networkSize;i++) {
					for (int j=0;j<FSONum;j++) {
							int k=this->activeSM[i][j];
							if (k==-1)
								count++;
					}
				}
				if ((ff*2+count)!=(this->networkSize*this->FSONum))
				{
						cout<<"Graph mismatch";
				}

			}

		}
	}
	int count=0;
	for (int i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
				int k=this->activeSM[i][j];
				if (k==-1)
					count++;
		}
	}

	if ((ff*2+count)!=(this->networkSize*this->FSONum))
				{
						cout<<"Graph mismatch";
				}
//#ifdef DEBUG
	if (!checkConsist())
		cout<<"ss";
//#endif

	for (int i=0;i<this->networkSize;i++) {
		cout << i << endl;
		for (int j=0;j<FSONum;j++) {
				int k=this->activeSM[i][j];
				if (k==-1) {
						addFSO(i,j);
#ifdef CheckConsistMacro						
						if (!checkConsist())
							cout<<"ss";
#endif
						ff++;
						count=0;
						for (int i=0;i<this->networkSize;i++) {
							for (int j=0;j<FSONum;j++) {
									int k=this->activeSM[i][j];
									if (k==-1)
										count++;
							}
						}
						if ((ff*2+count)!=(this->networkSize*this->FSONum))
									{
											cout<<"Graph mismatch";
									}

				}
		}
	}


	for (int i=0;i<this->networkSize;i++) {
		for (int j=0;j<FSONum;j++) {
				int k=this->activeSM[i][j];
				FSOSt f;
				f=this->FSOGraph[i][j][k];
//				this->topology[i][f.d]++;
				this->topology[f.d][i]++;
				assert(this->FSOGraph[f.d][f.FSO][f.SM].d==i);
				assert(this->FSOGraph[f.d][f.FSO][f.SM].FSO==j);
				assert(this->FSOGraph[f.d][f.FSO][f.SM].SM==k);
		}
	}

	for (int i=0;i<this->networkSize;i++) {
		for (int j=0;j<this->networkSize;j++) {
//				this->topology[i][f.d]++;
				assert(this->topology[i][j]==this->topology[j][i]);
		}
	}


	//cout<<ff;
}
bool networkControlLogic2::isConnectedInitFSO(int i,int j) {
	return true;
}
void networkControlLogic2::addFSO(int s, int SM) {
	if (findAlternatePathInitialFSO(s,SM)) {
		while (!this->alterPath.empty()) {
			FSOSt f=this->alterPath.front();
			this->alterPath.pop_front();
			FSOSt g=this->alterPath.front();
			this->alterPath.pop_front();
			g=debugfunc(f);
			this->activeSM[f.d][f.FSO]=f.SM;
			this->activeSM[g.d][g.FSO]=g.SM;
		}
	}
	else 
//		findAlternatePathInitialFSO(s,SM);
		throw "critical Error, Cannot find alternating path when constructing graph, uneven graph";
}
//	vector<vector<int> > elephentsNum;
// Elephent flows between source destination
//	vector<vector<long int> > elephentsVolume;
networkControlLogic2::networkControlLogic2(void)
{
}
networkControlLogic2::~networkControlLogic2(void)
{

}
FSOSt networkControlLogic2::debugfunc(FSOSt& g) {
	return this->FSOGraph[g.d][g.FSO][g.SM];
}
bool networkControlLogic2::findAlternatePathInitialFSO(int s, int FSO) {

	if (this->activeSM[s][FSO]>-1)
		throw "error trying to alternate from active FSO, init stage";

	this->alternatePath.resize(0);

	vector<FSOSt> alternateBFSInsert1;
	vector<FSOSt> alternateBFSInsert2;

	vector<vector< FSOSt> > checked1;
	vector<vector< FSOSt> > checked2;

	checked1.resize(this->networkSize);
	checked2.resize(this->networkSize);


	alternateBFSInsert1.resize(this->networkSize*this->FSONum);
	alternateBFSInsert2.resize(this->networkSize*this->FSONum);

	for (int i=0;i<this->networkSize*this->FSONum;i++) {
		alternateBFSInsert1[i].d=-1;
		alternateBFSInsert2[i].d=-1;
	}

	for (int i=0;i<this->networkSize;i++) {
		checked1[i].resize(this->networkSize);
		checked2[i].resize(this->networkSize);
		for (int j=0;j<this->FSONum;j++) {
			checked1[i][j].d=-1;
			checked2[i][j].d=-1;
		}
	}

	bool pathNotFound=true;
	int firstIndex=0;
	int secondIndex=0;
	int firstIndexEnd=-1;
	int secondIndexEnd=-1;

	alternateBFSInsert1[++firstIndexEnd].d=s;
	alternateBFSInsert1[firstIndexEnd].FSO=FSO;

	checked1[s][FSO].d=s;
	checked1[s][FSO].FSO=FSO;
	checked2[s][FSO].d=s;
	checked2[s][FSO].FSO=FSO;

	while (pathNotFound) {
		for (int ind=firstIndex;ind<=firstIndexEnd;ind++) {
			FSOSt n=alternateBFSInsert1[ind];
			for (int ii=0;ii<this->MirrorNum;ii++) {
				FSOSt g=debugfunc(n);
				g=this->FSOGraph[n.d][n.FSO][ii];
//		FSOSt g=this->FSOGraph[n.d][n.FSO][ii];
				if (checked2[g.d][g.FSO].d==-1)
				{
					if (this->activeSM[g.d][g.FSO]<=-1) {
						//finishing Stuffs
						FSOSt fin;
//						this->alterPath.push_front(g);
						checked2[g.d][g.FSO]=n;
						checked2[g.d][g.FSO].SM=ii;
						fin=g;
						while (!((fin.d==s) && (fin.FSO==FSO))) {
							this->alterPath.push_front(fin);
							fin=checked2[fin.d][fin.FSO];
							this->alterPath.push_front(fin);
							fin=checked1[fin.d][fin.FSO];
//							this->alterPath.push_front(fin);
						}
	//						this->alterPath.push_front(fin);
						return true;
					}
					else if (this->activeSM[n.d][n.FSO]==ii) continue;
//					assert(this->activeSM[g.d][g.FSO]!=g.SM);
					alternateBFSInsert2[++secondIndexEnd]=g;
					checked2[g.d][g.FSO]=n;
					checked2[g.d][g.FSO].SM=ii;

				}
			}
		}

		firstIndex=firstIndexEnd+1;
		if (secondIndex>secondIndexEnd) return false;

		for (int ind=secondIndex;ind<=secondIndexEnd;ind++) {
				FSOSt n=alternateBFSInsert2[ind];
				n.SM=this->activeSM[n.d][n.FSO];
				FSOSt g=this->FSOGraph[n.d][n.FSO][n.SM];
				//assert(this->activeSM[g.d][g.FSO]==g.SM);
				if (checked1[g.d][g.FSO].d==-1)
				{
					alternateBFSInsert1[++firstIndexEnd]=g;
					checked1[g.d][g.FSO]=n;
				}

		}


		secondIndex=secondIndexEnd+1;
		if (firstIndex>firstIndexEnd) return false;
	}
	return false;
}
bool networkControlLogic2::findAlternatePath(int s, int d,bool isConnected(int,int)) {
	if (s==d)
		throw "Finding Alternating path between same source Destination: Critical Error";
	this->alternatePath.resize(0);
	for (int i=0;i<this->networkSize;i++) {
		this->checked1[i]=-1;
		this->checked2[i]=-1;
		this->alternateBFS1[i]=-1;
		this->alternateBFS2[i]=-1;
	}
	bool pathNotFound=true;
	this->alternateBFS1[0]=s;
	int firstIndex=0;
	int secondIndex=-1;
	int firstIndexEnd=0;
	int secondIndexEnd=-1;
	while (pathNotFound) {
		for (int ind=firstIndex;ind<=firstIndexEnd;ind++) {
			int nextToProcess=this->alternateBFS1[ind];
			for (int i=0;i<networkSize;i++){
				if (
					(this->checked1[i]==-1) &&
					(isConnected(i,nextToProcess))
					)
				{
					this->checked1[i]=nextToProcess;
					this->alternateBFS2[++secondIndexEnd]=i;
				}
			}
		}
		firstIndex=firstIndexEnd+1;
		if (secondIndex>secondIndexEnd) return false;
		for (int ind=secondIndex;ind<=secondIndexEnd;ind++) {
			int nextToProcess=this->alternateBFS2[ind];
			for (int i=0;i<networkSize;i++){
				if (
					(this->checked2[i]==-1) &&
					!(isConnected(i,nextToProcess))
					)
				{
					if (i==d) {
						int next=d;
						this->checked2[i]=nextToProcess;
						while (next!=s) {
							this->alternatePath.push_front(next);
							next=this->checked2[next];
							this->alternatePath.push_front(next);
							next=this->checked1[next];
						}
					}
					this->checked2[i]=nextToProcess;
					this->alternateBFS1[++firstIndexEnd]=i;
				}
			}
		}
		secondIndex=secondIndexEnd+1;
		if (firstIndex>firstIndexEnd) return false;
	}
	return false;
}
void doSM(int n, int s, int& d) {
	if ((n == 512) && (s == 48) && (d == 14)) d = 10;
	if ((n == 256) && (s == 48) && (d == 12)) d = 10;
}
void doRSM(int n, int s, int& d) {
	if ((n == 512) && (s == 48) && (d == 10)) d = 14;
	if ((n == 256) && (s == 48) && (d == 10)) d = 12;
}

void networkControlLogic2::BFSOneNodeUpdateRoutestDBeam(int s) {
	BFSOneNodeUpdateRoutesAugment(s);
}
void networkControlLogic2::BFSOneNodeUpdateRoutescThrough(int s) {
	BFSOneNodeUpdateRoutesAugment(s);
}
void networkControlLogic2::BFSOneNodeUpdateRoutesAugment(int s) {
	
	//this->checkConsistant();
	static vector<int> parent;
	static vector<vector<int> > par;
	static vector<vector<edge> > par2;
	static vector<int> psize;
	static vector<int> psize2;
	static vector<int> p2size;
	static bool isInit=false;

	if (!isInit) {
		isInit=true;
		parent.resize(this->augNetworkSize);
		par.resize(this->augNetworkSize);
		psize.resize(this->augNetworkSize);
		psize2.resize(this->augNetworkSize);
		p2size.resize(this->augNetworkSize);
		par2.resize(this->augNetworkSize);
		for (int i=0;i<this->augNetworkSize;i++) {
			par[i].resize(this->maxPath);
			par2[i].resize(this->augNetworkSize);
		}
	}

	for (int i=0;i<this->augNetworkSize;i++) {
		parent[i]=-1;
		psize[i]=-1;
		psize2[i]=-1;
		p2size[i]=-1;
		par[i][0]=-1;
	}
	parent[s]=0;

	list<int> nodes;
	nodes.push_front(s);

	this->distances[s][s]=0;
	this->numberOfRoutes[s][s]=0;

	while (nodes.size()>0) {
		int n=nodes.front();
		nodes.pop_front();
		for (int i=0;i<this->augNetworkSize;i++) {
			if (this->topology[i][n]>0) {
				int fd=i;
				if (parent[fd]==-1) {
					this->numberOfRoutes[s][fd]=1;
					this->distances[s][fd]=this->distances[s][n]+1;
					parent[fd]=parent[n]+1;
					nodes.push_back(fd);
				}
				if (parent[fd]==parent[n]+1){
					this->numberOfRoutes[s][fd]=1;
					if (psize[fd]<this->maxPath-1) {
						if (parent[fd]<=2) {
							par[fd][++psize[fd]]=n;
						}
						else {
							par[fd][++psize[fd]]=par[n][rand()%(psize[n]+1)];
						}
					} else 
					if (psize[fd]<this->maxPath-1) {
						if ((rand()%psize2[fd])==0) {
							psize[fd]++;
								if (parent[fd]<=2)  {
									par[fd][rand()%maxPath]=n;
								}
								else {
									par[fd][rand()%maxPath]=par[n][rand()%(psize[n]+1)];
								}
						}
					}
				}
			}
		}
	}

	for (int i=0;i<s;i++) {
		if (this->topology[s][i]>0) {
			this->RoutingTable[s][i].resize(1);
			this->RoutingTable[s][i][0].first=i;
			this->RoutingTable[s][i][0].second=0;
			this->RoutingTable2[s][i].resize(1);
			this->RoutingTable2[s][i][0].first=i;
			this->RoutingTable2[s][i][0].second=0;
	
			if (isMiniNet) {
				if (!this->routingHops[s][i][i]) {
					this->routingHops[s][i][i]=true;
					this->miniNetRuleUpdate1(s,i,i);
					}
			}


			updateFlow++;
			continue;
		}
		this->RoutingTable[s][i].resize(psize[i]+1);
		this->RoutingTable2[s][i].resize(psize[i]+1);
		for (int j=0;j<=psize[i];j++) {
			this->RoutingTable[s][i][j].first=par[i][j];
			this->RoutingTable[s][i][j].second=0;
			this->RoutingTable2[s][i][j].first=par[i][j];
			this->RoutingTable2[s][i][j].second=0;

			if (isMiniNet) {
				if (!this->routingHops[s][i][par[i][j]]) {
					this->routingHops[s][i][par[i][j]]=true;
					this->miniNetRuleUpdate1(s,i,par[i][j]);
					}
			}
			updateFlow++;
		}

	}
	this->RoutingTable[s][s].resize(0);
	this->RoutingTable2[s][s].resize(0);
	for (int i=s+1;i<this->augNetworkSize;i++) {
		if (this->topology[s][i]>0) {
			this->RoutingTable[s][i].resize(1);
			this->RoutingTable[s][i][0].first=i;
			this->RoutingTable[s][i][0].second=0;
			this->RoutingTable2[s][i].resize(1);
			this->RoutingTable2[s][i][0].first=i;
			this->RoutingTable2[s][i][0].second=0;

			if (isMiniNet) {
				if (!this->routingHops[s][i][i]) {
					this->routingHops[s][i][i]=true;
					this->miniNetRuleUpdate1(s,i,i);
					}
			}

			updateFlow++;
			continue;
		}
		this->RoutingTable[s][i].resize(psize[i]+1);
		this->RoutingTable2[s][i].resize(psize[i]+1);
		for (int j=0;j<=psize[i];j++) {
			if (s==par[i][j]) {
				this->RoutingTable[s][i][j].first=i;
				this->RoutingTable[s][i][j].second=0;
				this->RoutingTable2[s][i][j].first=i;
				this->RoutingTable2[s][i][j].second=0;
				if (isMiniNet) {
					if (!this->routingHops[s][i][i]) {
						this->routingHops[s][i][i]=true;
						this->miniNetRuleUpdate1(s,i,i);
						}
				}
				continue;					
			}
			this->RoutingTable[s][i][j].first=par[i][j];
			this->RoutingTable[s][i][j].second=0;
			this->RoutingTable2[s][i][j].first=par[i][j];
			this->RoutingTable2[s][i][j].second=0;
			if (isMiniNet) {
				if (!this->routingHops[s][i][par[i][j]]) {
					this->routingHops[s][i][par[i][j]]=true;
					this->miniNetRuleUpdate1(s,i,par[i][j]);
					}
			}
			updateFlow++;
		}
	}
}


int networkControlLogic2::get_FlowCount(int currentHop, string flowID)
{
	return FlowRoutingTable[currentHop].count(flowID);

}

/* Added for fs */
BOOST_PYTHON_MODULE(networkControlLogic2module)
{
    //	vector< vector< vector<std::pair<int,int> > > >	RoutingTable;
    // 	map<int, map<string, std::pair<int,int> > > FlowRoutingTable;
    // 	vector<vector<int> > topology;
    /*enum trafficAlgorithm {
    tDBeam,
    cThrough,
    oursCongestion,
    oursNoFlowRouting,
    };*/
    /*
	vector<vector<long int> > trafficVolume;
	vector<vector<int> > elephentsNum;
	vector<vector<long int> > elephentsVolume;
	vector<vector<long int> > trafficVolumeInTransit;
	vector<vector<int> > elephentsNumInTransit;
	vector<vector<long int> > elephentsVolumeInTransit;
    */
    using namespace boost::python;

    class_<std::vector<long int> >("long_vector")
    .def(vector_indexing_suite<std::vector<long int> >())
    ;

    class_<std::vector<int> >("int_vector")
    .def(vector_indexing_suite<std::vector<int> >())
    ;

    class_<std::pair<int, int> >("int_pair")
    .def_readwrite("first", &std::pair<int, int>::first)
    .def_readwrite("second", &std::pair<int, int>::second)
    ;

    enum_<trafficAlgorithm>("traffic_Algorithm")
    .value("tDBeam", tDBeam)
    .value("cThrough", cThrough)
    .value("oursCongestion", oursCongestion)
    .value("jellyFish", jellyFish)
    .value("oursNoFlowRouting", oursNoFlowRouting)
    .value("fatTree", fatTree)
    .export_values()
    ;

    typedef vector<long int> longvector;
    typedef vector<int> intvector;
    typedef std::pair<int, int>  intpair;
    typedef std::vector<intpair>  intpairvector;

    ////////////////////////////////////////////////////

    class_<std::vector<intvector> >("intvector_vector")
    .def(vector_indexing_suite<std::vector<intvector> >())
    ;
    class_<std::vector<longvector> >("longvector_vector")
    .def(vector_indexing_suite<std::vector<longvector> >())
    ;
    class_<std::vector<intpair> >("intpair_vector")
    .def(vector_indexing_suite<std::vector<intpair> >())
    ;

    class_< vector< intpairvector> >("intpairv_vector")
    .def(vector_indexing_suite < vector< intpairvector> >())
    ;
    class_<vector< vector< intpairvector > >>("intpairvv_vector")
    .def(vector_indexing_suite<vector< vector< intpairvector> >>())
    ;

    ////////////////////////////////////////////////////
    class_<std::map<string, intpair>> ("stringpair_map")
    .def(map_indexing_suite<std::map<string, intpair>>())
    ;

    class_<std::map<int, intpairvector>> ("intvector_map")
    .def(map_indexing_suite<std::map<int, intpairvector>>())
    ;
    class_<map<int, map<string, std::pair<int,int> > >> ("intvector_mapmap")
    .def(map_indexing_suite<map<int, map<string, std::pair<int,int> > >>())
    ;

    typedef std::map<string,intpair> stringpairmap;
    typedef std::map<int, intpairvector> intvectormap;

    ////////////////////////////////////////////////////
    def("vectorSizeCalc", vectorSizeCalc)
    ;

    class_<std::map<int, std::map<int, intpairvector> >> ("intmap_map")
    .def(map_indexing_suite<std::map<int, std::map<int, intpairvector> >>())
    ;

    class_<std::map<string,intvectormap >> ("stringmap_map")
    .def(map_indexing_suite<std::map<string, intvectormap>>())
    ;

    class_<networkControlLogic2>("networkControlLogic2class")
     .def("initilize", &networkControlLogic2::initilize)
     .def("initilizeFS", &networkControlLogic2::initilizeFS)
     .def("initilizeMiniNet", &networkControlLogic2::initilizeMiniNet)
     .def("elephantFlowArrival", &networkControlLogic2::elephantFlowArrival)
     .def("elephantFlowEnd", &networkControlLogic2::elephantFlowEnd)
     .def("computTopo", &networkControlLogic2::computTopo)
     .def("get_FlowCount", &networkControlLogic2::get_FlowCount)
     .def_readwrite("initTopology", &networkControlLogic2::initTopology)
     .def_readwrite("nextTimer", &networkControlLogic2::nextTimer)
     .def_readwrite("topology", &networkControlLogic2::topology)
     .def_readwrite("additionalTopology", &networkControlLogic2::additionalTopology)
     .def_readwrite("initAdditionalTopology", &networkControlLogic2::initAdditionalTopology)
     .def_readwrite("FlowRoutingTable", &networkControlLogic2::FlowRoutingTable)
     .def_readwrite("RoutingTable", &networkControlLogic2::RoutingTable)
     .def_readwrite("trafficVolume", &networkControlLogic2::trafficVolume)
     .def_readwrite("elephentsNum", &networkControlLogic2::elephentsNum)
     .def_readwrite("elephentsVolume", &networkControlLogic2::elephentsVolume)
     .def_readwrite("trafficVolumeInTransit", &networkControlLogic2::trafficVolumeInTransit)
     .def_readwrite("elephentsNumInTransit", &networkControlLogic2::elephentsNumInTransit)
     .def_readwrite("elephentsVolumeInTransit", &networkControlLogic2::elephentsVolumeInTransit)
    ;

}
/*******************************/
