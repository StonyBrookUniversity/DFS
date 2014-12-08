
#ifndef randomGraphGenerator_H
#define randomGraphGenerator_H
#include <vector>
#include <map>
#include <list>

using namespace std;

class randomGraph
{
private:
	void addAugmentedPath1(vector<vector<int> >& g,vector<int>& deg,int s,int degree);
	void addAugmentedPath2(vector<vector<int> >& g,vector<int>& deg,int s,int degree,int nodes,int snodes);

public:
	static int treshold;
		
	vector<vector<int> > randomRegularGraph(int nodes,int degree);
	vector<vector<int> > randomJellyGraph(int nodes,int degree,int snodes=0);
//	vector<vector<int> > randomBipartiteGraph(int nodes,int degree);
};

#endif

