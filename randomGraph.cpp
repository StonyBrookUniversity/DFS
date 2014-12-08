
#include "randomGraph.h"
#include <iostream>
#include <algorithm>  
#pragma warning(disable:4503)
#pragma warning(disable:4018)

int randomGraph::treshold=1;

void randomGraph::addAugmentedPath1(vector<vector<int> >& g,vector<int>& deg,int s,int degree) {

	list<int> l1;
	list<int> l0;
	vector<int> p0(g.size(),-1);
	vector<int> p1(g.size(),-1);
	p0[s]=p1[s]=s;
	deg[s]++;
	l0.push_front(s);
	bool notFinished=true;
	while (notFinished) {
		while (!l0.empty()) {
			int nextNode=l0.front();
			l0.pop_front();
			for (int i=0;i<g.size();i++) {
				if ((p1[i]==-1) && (g[nextNode][i]==0)) {
					l1.push_back(i);
					p1[i]=nextNode;
					if (deg[i]<degree) {
							notFinished=false;
							break;
					}
				}
			}
			if (!notFinished) break;
		}
		if (p0[s]==s)
			p0[s]=p1[s]=-1;
		if (!notFinished) break;
		while (!l1.empty()) {
			int nextNode=l1.front();
			l1.pop_front();
			for (int i=0;i<g.size();i++) {
				if ((p0[i]==-1) && (g[nextNode][i]==1)) {
					l0.push_back(i);
					p0[i]=nextNode;
				}
			}
		}
		if (l0.empty()) 
			throw "Error adding augmenting path, Check the parameters";
	}
	int n=l1.back();
	int p=p1[n];

	deg[n]++;
	

	g[n][p]++;
	g[p][n]++;

	while (p!=s) {
		n=p;
		p=p0[n];

		g[n][p]--;
		g[p][n]--;

		n=p;
		p=p1[n];

		g[n][p]++;
		g[p][n]++;
	}
}


void randomGraph::addAugmentedPath2(vector<vector<int> >& g,vector<int>& deg,int s,int degree, int nodes,int snodes) {
	
	list<int> l1;
	list<int> l0;
	vector<int> p0(snodes,-1);
	vector<int> p1(snodes,-1);

	s=s-nodes;
	p0[s]=p1[s]=s;
	deg[nodes+s]++;
	l0.push_front(s);
	bool notFinished=true;
	while (notFinished) {
		while (!l0.empty()) {
			int nextNode=l0.front();
			l0.pop_front();
			for (int i=0;i<snodes;i++) {
				if ((p1[i]==-1) && (g[nodes+nextNode][nodes+i]==0)) {
					l1.push_back(i);
					p1[i]=nextNode;
					if (deg[nodes+i]<2*degree) {
						notFinished=false;
						break;
					}
				}
			}
			if (!notFinished) break;
		}
		if (p0[s]==s)
			p0[s]=p1[s]=-1;
		if (!notFinished) break;
		while (!l1.empty()) {
			int nextNode=l1.front();
			l1.pop_front();
			for (int i=0;i<snodes;i++) {
				if ((p0[i]==-1) && (g[nodes+nextNode][nodes+i]==1)) {
					l0.push_back(i);
					p0[i]=nextNode;
				}
			}
		}
		if (l0.empty()) 
			throw "Error adding augmenting path, Check the parameters";
	}
	int n=l1.back();
	int p=p1[n];

	deg[nodes+n]++;

	g[nodes+n][nodes+p]++;
	g[nodes+p][nodes+n]++;

	while (p!=s) {
		n=p;
		p=p0[n];

		g[nodes+n][nodes+p]--;
		g[nodes+p][nodes+n]--;

		n=p;
		p=p1[n];

		g[nodes+n][nodes+p]++;
		g[nodes+p][nodes+n]++;
	}
}





vector<vector<int> > randomGraph::randomRegularGraph(int nodes,int degree) {
	if ((nodes*degree%2)==1)
		throw "Error, cannot create a regular random graph with odd number of nodes or degree";
	if (degree>=nodes) 
		throw "Error, cannot have more edges than nodes";
	vector<vector<int> > res;
	res.resize(nodes);
	for (int i=0;i<nodes;i++) 
		res[i]=vector<int>(nodes,0);
	vector<int> deg(nodes,0);
	
	int attempts=0;
	int edges=nodes*degree/2;
	
	while ((edges>0) && (++attempts) < this->treshold) {
		int i=rand()%nodes;
		int j=rand()%nodes;
		if ((i!=j) && (res[i][j]==0) && (max(deg[i],deg[j])<degree)) {
			attempts=0;
			res[i][j]=res[j][i]=1;
			edges--;
			deg[i]++;
			deg[j]++;
		}
	}//*/
	map<int,int> remainingNodes;
	map<int,int>::iterator it;
	for (int i=0;i<nodes;i++) {
		if (deg[i]<degree)
			remainingNodes[i]=degree-deg[i];
	}
	for (it=remainingNodes.begin();it!=remainingNodes.end();it++) {
			while (deg[it->first]<degree)
				addAugmentedPath1(res,deg,it->first,degree);
	}
	return res;
}


vector<vector<int> > randomGraph::randomJellyGraph(int nodes,int degree,int snodes){
	if (snodes==0) snodes=3*nodes;
	if (snodes<nodes)
		throw "Cannot create a jellyFish with less steiner nodes than normal ones";
	if ((nodes*degree%2)==1)  
		throw "Error, cannot create a regular random graph with odd number of nodes or degree";
	if (degree>=min(snodes,2*nodes)) 
		throw "Error, cannot have more edges than nodes";
	vector<vector<int> > res;
	res.resize(nodes+snodes);
	for (int i=0;i<nodes+snodes;i++) 
		res[i]=vector<int>(nodes+snodes,0);
	vector<int> deg(nodes+snodes,0);
	int attempts=0;
	int edges=nodes*degree;
	while ((edges>0) && (++attempts) < this->treshold) {
		int i=rand()%nodes;
		int j=nodes+rand()%snodes;
		if ((res[i][j]==0) && (deg[i]<degree) && (deg[j]<2*(degree-1))) {
			attempts=0;
			res[i][j]=res[j][i]=1;
			edges--;
			deg[i]++;
			deg[j]++;
		}
	}//*/
	map<int,int> remainingNodes;
	map<int,int> remainingNodes2;
	map<int,int>::iterator it,it2;

	attempts=0;
	for (int i=0;i<nodes;i++) 
		if (deg[i]<degree)
			remainingNodes[i]=degree-deg[i];
	
	for (it=remainingNodes.begin();it!=remainingNodes.end();it++) {
		for (int f=0;f<it->second;f++) {
			int i=it->first;
			attempts=0;
			int j=nodes+rand()%snodes;
			while ((++attempts<treshold) && ((res[i][j]==0) && (deg[i]<degree) && (deg[j]<2*(degree-1)))) 
				j=nodes+rand()%snodes;
			attempts=0;
			res[i][j]=res[j][i]=1;
			edges--;
			deg[i]++;
			deg[j]++;
		}
	}

	if (edges>0) {
		remainingNodes.clear();
		for (int i=0;i<nodes;i++) 
			if (deg[i]<degree)
				remainingNodes[i]=degree-deg[i];
		for (int i=nodes;i<nodes+snodes;i++) 
			if (deg[i]<2*(degree-1))
				remainingNodes2[i]=2*(degree-1)-2*(deg[i]-1);
		for (it=remainingNodes.begin();it!=remainingNodes.end();it++) {
			for (int f=0;f<it->second;f++) {
				int i=it->first;
				int j=rand()% remainingNodes2.size();
				for (it2=remainingNodes2.begin();j>0;it2++,j--);
				j=it2->first;
				it2->second--;
				if (it2->second==0) remainingNodes2.erase(j);
				if ((res[i][j]==0) && (deg[i]<degree) && (deg[j]<2*(degree-1))) {
					attempts=0;
					res[i][j]=res[j][i]=1;
					edges--;
					deg[i]++;
					deg[j]++;
				}
				else {
					throw "Error in constructing jellyFish, check the augmenting link, first phase, third attempt";
				}
			}
		}
	}

	attempts=0;
	edges=snodes*2*degree-snodes*degree;
	while ((edges>0) && (++attempts) < this->treshold) {
		int i=nodes+rand()%snodes;
		int j=nodes+rand()%snodes;
		if ((i!=j) && (res[i][j]==0) && (max(deg[i],deg[j])<2*degree)) {
			attempts=0;
			res[i][j]=res[j][i]=1;
			edges--;
			deg[i]++;
			deg[j]++;
		}
	}//*/

	remainingNodes.clear();

	for (int i=nodes;i<nodes+snodes;i++) {
		if (deg[i]<2*degree)
			remainingNodes[i]=2*degree-deg[i];
	}

	for (it=remainingNodes.begin();it!=remainingNodes.end();it++) {
			while (deg[it->first]<2*degree)
				addAugmentedPath2(res,deg,it->first,degree,nodes,snodes);
	}
	return res;
}
