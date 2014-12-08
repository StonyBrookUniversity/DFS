#include "networkControlLogic2.h"
#include <fstream>
//#include <boost/algorithm/string.hpp>   
#include <string.h>
#include <stdio.h>
#include "Source.h"
#include <string.h>



using namespace std;

void parseLog() {
	ifstream myfile;
	myfile.open("error2log.txt");
	string s;
	char ds[5000];
	ds[0] = 0;
	getline(myfile, s);
	networkControlLogic2 *a;
	a = new networkControlLogic2();
	int sizen = 64;
	int FSO = 48;
	int SM=10;
	//boost::to_lower(s);
//	sscanf(s.c_str(), "networkControlLogic2object.initilize(%d,%d,%d%*", &sizen, &FSO, &SM);
	a->initilize(sizen, FSO, SM, oursCongestion);
	char fid[500];
	char* sid=fid+sizeof(char);
	int ss = 3;
	int d=0;
	Sim_Timer t = 0;
	
	while (!myfile.eof()) {
		getline(myfile, s);
		strcpy(ds, s.c_str());
		if (s.size() < 1) continue;
		if (s[0]=='#') continue;
		if (s.find("networkControlLogic2object.elephantFlowArrival") != -1) {
			char dds[500];
			if (s.find("status") != -1) {
				cout << "sss";
				sscanf(ds, "status=networkControlLogic2object.elephantFlowArrival('%[^']', %d , %d , %s)", fid, &ss, &d, dds);
			}
			else {
				sscanf(ds, "networkControlLogic2object.elephantFlowArrival('%[^']', %d , %d , %s)", fid, &ss, &d, dds);
			}
			t = strtoll(dds, NULL, 10);
			a->elephantFlowArrival(fid, ss, d, t);
		}
		else
		if (s.find("networkControlLogic2object.elephantFlowEnd")!=-1) {
			char dds[500];
			sscanf(ds, "networkControlLogic2object.elephantFlowEnd('%[^']', %d , %d , %s)", fid, &ss, &d, dds);
			t = strtoll(dds,NULL,10);
			a->elephantFlowArrival(fid, ss, d, t);
		}
		else
		if (s.find("networkControlLogic2object.elephentsVolumeInTransit") != -1) {
			int t = 0;
			char ff = 0;
			sscanf(ds, "networkControlLogic2object.elephentsVolumeInTransit[ %d ][ %d ]%c= %d", &ss, &d, &ff, &t);
			if (ff == '+')
				a->elephentsVolumeInTransit[ss][d] += t;
			else if (ff == '-')
				a->elephentsVolumeInTransit[ss][d] -= t;
			else
				throw "error";
		}
		else
		if (s.find("networkControlLogic2object.elephentsVolume") != -1) {
			int t = 0;
			char ff = 0;
			sscanf(ds, "networkControlLogic2object.elephentsVolume[ %d ][ %d ]%c= %d", &ss, &d, &ff, &t);
				if (ff == '+')
					a->elephentsVolume[ss][d] += t;
			else if (ff == '-')
				a->elephentsVolume[ss][d] -= t;
			else
				throw "error";
		}
		else
		if (s.find("networkControlLogic2object.trafficVolumeInTransit") != -1) {
			int t = 0;
			char ff = 0;
			sscanf(ds, "networkControlLogic2object.trafficVolumeInTransit[ %d ][ %d ]%c= %d", &ss, &d, &ff, &t);
			if (ff == '+')
				a->trafficVolumeInTransit[ss][d] += t;
			else if (ff == '-')
				a->trafficVolumeInTransit[ss][d] -= t;
			else
				throw "error";
		}
		else
		if (s.find("networkControlLogic2object.trafficVolume") != -1) {
			int t = 0;
			char ff = 0;
			sscanf(ds, "networkControlLogic2object.trafficVolume[ %d ][ %d ]%c= %d", &ss, &d,&ff,&t);
			if (ff=='+')
				a->trafficVolume[ss][d] += t;
			else if (ff == '-')
				a->trafficVolume[ss][d] -= t;
			else
				throw "error";
		}
		else
		if (s.find("networkControlLogic2object.elephentsNum") != -1) {
			int t = 0;
			char ff = 0;
			sscanf(ds, "networkControlLogic2object.elephentsNum[ %d ][ %d ]%c= %d", &ss, &d, &ff, &t);
			if (ff == '+')
				a->elephentsNum[ss][d] += t;
			else if (ff == '-')
				a->elephentsNum[ss][d] -= t;
			else
				throw "error";
		}
		else if (s.find("Traceback (most recent call last)") != -1) {
			unordered_map<string, flow>::iterator it2;
//			for (it = a->elephentsInTheSystem.begin(); it != a->elephentsInTheSystem.end(); it++) {
			for (auto& it : a->elephentsInTheSystem) {
				for (auto& kv : it.second.edgesUsed) {
					int g=a->FlowRoutingTable[kv.s].count(it.second.flowID);
					if (g == 0) {
						std::cout << "screwed";
					}
					else if (g == 1) {
						if (kv.d != a->FlowRoutingTable[kv.s][it.second.flowID].first) {
							std::cout << "screwed";
						}

					} else
						std::cout << "screwed";
				}
				for (auto& kv : it.second.edgesUsed2) {
					int g = a->FlowRoutingTable[kv.s].count(it.second.flowID);
					if (g == 0) {
						std::cout << "screwed";
					}
					else if (g == 1) {
						if (kv.d == a->FlowRoutingTable[kv.s][it.second.flowID].first) {
							std::cout << "screwed";
						}

					}
					else
						std::cout << "screwed";
				}
			}
		}
	}
	std::cout << "done";
}
