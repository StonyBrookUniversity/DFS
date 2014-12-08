// Re-Configc++.cpp : Defines the entry point for the console application.
// ifstream constructor.

#define DEBUG


#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
//#include "netInterface.h"

#include "networkControlLogic2.h"


using namespace std;

int main(void)
{

	char buff[500];
	int sizen=128;

	networkControlLogic2 a;
	clock_t t1=clock();
	for (int i=0;i<128;i++)
		for (int j=0;j<128;j++)
			a.RoutingTable[i][j].resize(4);

	a.initilize(128,20,20,oursNoFlowRouting);
	clock_t t2=clock();
	cout<<(t2-t1)<<"  "<<CLOCKS_PER_SEC<<endl;




	ofstream out;
	out.open("log.txt");

	//*/
	for (int i=0;i<128;i++) {
		for (int j=0;j<128;j++) {
			out<<a.topology[i][j]<<"  ";
		}
		out<<endl;
	}//*/
	out.close();
/*	cout<<a.isConnected()<<endl;
	FSOSt f,g;
	for (int i=0;i<19;i++) {
		if (true) {
			f=a.FSOGraph[0][i][a.activeSM[0][i]];
			g=a.FSOGraph[f.d][f.FSO][f.SM];
			a.activeSM[0][i]=-1;
			a.activeSM[f.d][f.FSO]=-1;
		}
	}
//	cout<<a.isConnected()<<endl;
	f=a.FSOGraph[0][19][a.activeSM[0][19]];
//	g=a.FSOGraph[f.d][f.FSO][f.SM];
	cout<<a.topology[0][f.d]<<endl;
	a.topology[0][f.d]=1;
	//*/
	vector<vector<vector<int> > > some;
	int*** ss;

	int ff=500;
	some.resize(ff);
	ss=new int**[ff];
	for (int i=0;i<ff;i++) {
		some[i].resize(ff);
		ss[i]=new int*[ff];
		for (int j=0;j<ff;j++) {
			ss[i][j]=new int[ff];
			some[i][j].resize(ff);
				for (int f=0;f<ff;f++) {
					some[i][j][f]=f;
					ss[i][j][f]=f;
				}
		}
	}

	for (int i=0;i<128;i++)
		for (int j=0;j<128;j++)
			a.checkRemainConnected(i,j);
	int sum=0;
	cout<<endl<<endl<<endl;
	t1=clock();
	for (int i=0;i<ff;i++) 
		for (int j=0;j<ff;j++) 
				for (int f=0;f<ff;f++) 
					sum=sum+some[i][j][f];
	t2=clock();
	cout<<(t2-t1)<<"  "<<CLOCKS_PER_SEC<<endl;
	int sum1=0;

	cout<<endl;
	t1=clock();
	for (int i=0;i<ff;i++) 
		for (int j=0;j<ff;j++) 
				for (int f=0;f<ff;f++) 
					sum1=sum1+ss[i][j][f];
	t2=clock();
	cout<<(t2-t1)<<"  "<<CLOCKS_PER_SEC<<endl;


	for (int i=0;i<ff;i++) {
		for (int j=0;j<ff;j++) 
					delete ss[i][j];
		delete ss[i];
	}
	delete ss;

	cout<<sum<<" "<<sum1;

	int i;
	std::cin>>i;
	return 0;
}

