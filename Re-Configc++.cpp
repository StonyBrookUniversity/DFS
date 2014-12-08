// Re-Configc++.cpp : Defines the entry point for the console application.
// ifstream constructor.



#include "stdafx.h"
#include <stdlib.h>
#include "randomGraph.h"
#include "GenerateFattree.h"

#define DEBUG

#pragma warning(disable:4018)
#pragma warning(disable:4503)



#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <memory>      
#include "GenerateFattree.h"
//#include "netInterface.h"

#include "networkControlLogic2.h"


using namespace std;

bool flipACoin2() {
	if (rand()%2)
		return true;
	else return false;
}

int main(void)
{
//	char buff[500];

	vector<vector<vector<bool> > > ee(512,vector<vector<bool> >(512, vector<bool>(512,false)));
	vector<int> fffdf;
	vector<int>::iterator ffs;
	
	std::ofstream out("out.txt");	
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
//    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!	
	



	networkControlLogic2 *a;
	a=new networkControlLogic2();
	


	int sizen=64;
	
	a->initilizeMiniNet(sizen,16,8,oursCongestion);
	cout<<a->elephentsInTheSystem.size()<<endl;
//	return 1;
	Sim_Timer ss=SIMULATION_CLOCK_PER_MICRO_SECOND*1000;
	Sim_Timer sfd=0;

	clock_t t1=clock();
	for (int j=1;j<20;j++) {
		for (int i=0;i<2000;i++) {
			char buf[500];
			sprintf_s(buf,"f%d",j*2000+i);
			std::string s(buf);
			int h=rand()%sizen;
			int k=rand()%sizen;
			while (h==i) h=rand()%sizen;
			a->elephantFlowArrival(s,k,h,sfd);
//			if (a->elephentsInTheSystem.size()!=(i-1))
	//			cout<<(a->elephentsInTheSystem.size())<<"  "<<buf<<endl;
			sfd+=ss;
		}
		cout<<"Elepehnt in the system are "<<a->elephentsInTheSystem.size()<<endl;
		clock_t t2=clock();
		cout<<(t2-t1)<<"  "<<CLOCKS_PER_SEC<<endl;
		t1=clock();
		for (int i=0;i<200;i++) {
			a->computTopo(sfd);
			sfd+=ss;
		}
		out.flush();
		
		t2=clock();
		cout<<(t2-t1)<<"  "<<CLOCKS_PER_SEC<<endl;
		t1=clock();

		for (int i=0;i<2000;i++) {
			char buf[500];
			sprintf_s(buf,"f%d",j*2000+i);
			std::string s(buf);
			int h=0;
			a->elephantFlowEnd(s,i,h,sfd);
			sfd+=ss;
		}
//		a->computTopo();
		cout<<"Elepehnt in the system are "<<a->elephentsInTheSystem.size()<<endl;
		out.flush();
	}
	cout<<"Ended "<<a->elephentsInTheSystem.size()<<endl;
	out.close();
	return 0;

//	a->computTopo(200000000000);
	delete(a);
	a=new networkControlLogic2();
	a->initilize(sizen,3,2,tDBeam);
	delete(a);


	a=new networkControlLogic2();
	a->initilize(sizen,3,2,cThrough);
	a->computTopo(1000);
	



	clock_t t2=clock();
	cout<<(t2-t1)<<"  "<<CLOCKS_PER_SEC<<endl;




	//ofstream out;
	out.open("log.csv");

	//*/
	for (int i=0;i<sizen;i++) {
		int j;
		for (j=0;j<sizen-1;j++) {
			out<<min(1,a->topology[i][j])<<",";
		}
		out<<min(1,a->topology[i][sizen-1]);
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
	return 0;
	vector<vector<vector<int> > > some;
	int*** sss;

	int ff=500;
	some.resize(ff);
	sss=new int**[ff];
	for (int i=0;i<ff;i++) {
		some[i].resize(ff);
		sss[i]=new int*[ff];
		for (int j=0;j<ff;j++) {
			sss[i][j]=new int[ff];
			some[i][j].resize(ff);
				for (int f=0;f<ff;f++) {
					some[i][j][f]=f;
					sss[i][j][f]=f;
				}
		}
	}

	for (int i=0;i<128;i++)
		for (int j=0;j<128;j++)
			a->checkRemainConnected(i,j);
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
					sum1=sum1+sss[i][j][f];
	t2=clock();
	cout<<(t2-t1)<<"  "<<CLOCKS_PER_SEC<<endl;


	for (int i=0;i<ff;i++) {
		for (int j=0;j<ff;j++) 
					delete sss[i][j];
		delete sss[i];
	}
	delete sss;

	cout<<sum<<" "<<sum1;

	int i;
	std::cin>>i;
	return 0;
}

