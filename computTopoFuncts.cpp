#pragma warning(disable:4503)
#pragma warning(disable:4018)

#include "navidConstants.h"
#include "networkControlLogic2.h"

void networkControlLogic2::cmpTopoJellyfish(Sim_Timer time) {
	return;
}



void networkControlLogic2::cmpTopocThrough(Sim_Timer time) {
	timeEvent t;
	currentTime=time;
	while (!this->nextsCall.empty()) {
		int sss=this->nextsCall.size();
		t=this->nextsCall.front();
		if (t.t<currentTime) {
			this->nextsCall.pop_front();
			activateLinkcThrough(t.s, t.d);
		}
		else break;
	}
	if ((time-lastReconfig)>PRIODICTIME_CTHROUGH) {
		lastReconfig+=PRIODICTIME_FIRFLY;
		while (this->unprocessesFlows.size()>0) {
			processNextcThrough(this->unprocessesFlows.front());
			this->unprocessesFlows.pop_front();
			lastReconfig=currentTime;
			nextReconfig=lastReconfig+priodicTime;
		}
	}
	if (this->nextsCall.size()>0) {
		nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND*this->nextsCall.front().t;
		//this->nextsCall.pop_front();
	}
	else { nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND;
			nextTimer=nextTimer*50000;
	}
	return;
}


void networkControlLogic2::cmpTopotDBeam(Sim_Timer time) {
	currentTime=time;
	timeEvent t;
	while (!this->nextsCall.empty()) {
		int sss=this->nextsCall.size();
		t=this->nextsCall.front();
		if (t.t<currentTime) {
			this->nextsCall.pop_front();
			activateLinktDBeam(t.s, t.d);
		}
		else break;
	}
	while (this->unprocessesFlows.size()>0) {
		processNexttDBeam(this->unprocessesFlows.front());
		this->unprocessesFlows.pop_front();
		lastReconfig=currentTime;
		nextReconfig=lastReconfig+priodicTime;
	}
	if (this->nextsCall.size()>0) {
		nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND*this->nextsCall.front().t;
		//this->nextsCall.pop_front();
	}
	else { nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND;
			nextTimer=nextTimer*50000;
		 }
	return;
}


void networkControlLogic2::cmpTopoOursCongestion(Sim_Timer time) {
	currentTime=time;
	timeEvent t;
	while (!this->nextsCall.empty()) {
		int sss=this->nextsCall.size();
		t=this->nextsCall.front();
		if (t.t<currentTime) {
			this->nextsCall.pop_front();
			activateLink(t);
		}
		else break;
	}
	while (this->unprocessesFlows.size()>0) {
		processNextElephent(this->unprocessesFlows.front());
		this->unprocessesFlows.pop_front();
		lastReconfig=currentTime;
		nextReconfig=lastReconfig+priodicTime;
	}
	if (this->nextsCall.size()>0) {
		nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND*this->nextsCall.front().t;
		//this->nextsCall.pop_front();
	}
	else { nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND;
			nextTimer=nextTimer*50000;
		 }
	return;
}

void networkControlLogic2::cmpoursNoFlowRouting(Sim_Timer time) {
	currentTime=time;
	timeEvent t;
	while (!this->nextsCall.empty()) {
		int sss=this->nextsCall.size();
		t=this->nextsCall.front();
		if (t.t<currentTime) {
			this->nextsCall.pop_front();
			activateLink(t);
		}
		else break;
	}
	while (this->unprocessesFlows.size()>0) {
		processNextElephent(this->unprocessesFlows.front());
		this->unprocessesFlows.pop_front();
		lastReconfig=currentTime;
		nextReconfig=lastReconfig+priodicTime;
	}
	if (this->nextsCall.size()>0) {
		nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND*this->nextsCall.front().t;
		//this->nextsCall.pop_front();
	}
	else { nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND;
			nextTimer=nextTimer*50000;
		 }
	return;
}


void networkControlLogic2::cmpourPriodicReconfig(Sim_Timer time) {
	timeEvent t;
	currentTime=time;
	while (!this->nextsCall.empty()) {
		int sss=this->nextsCall.size();
		t=this->nextsCall.front();
		if (t.t<currentTime) {
			this->nextsCall.pop_front();
			activateLink(t);
		}
		else break;
	}
	if ((time-lastReconfig)>PRIODICTIME_FIRFLY) {
		lastReconfig+=PRIODICTIME_FIRFLY;
		while (this->unprocessesFlows.size()>0) {
			processNextElephent(this->unprocessesFlows.front());
			this->unprocessesFlows.pop_front();
			lastReconfig=currentTime;
			nextReconfig=lastReconfig+priodicTime;
		}
	}
	if (this->nextsCall.size()>0) {
		nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND*this->nextsCall.front().t;
		//this->nextsCall.pop_front();
	}
	else { nextTimer=SIMULATION_CLOCK_PER_MICRO_SECOND;
			nextTimer=nextTimer*50000;
	}
	return;
}


int networkControlLogic2::computTopo(Sim_Timer time) {
	switch (this->alg) {
	case tDBeam:
		cmpTopotDBeam(time);
		break;
	case ourPriodicReconfig:
		cmpourPriodicReconfig(time);
	case cThrough:
		cmpTopocThrough(time);
		break;
	case jellyFish:
		cmpTopoJellyfish(time);
		break;
	case oursCongestion:
		cmpTopoOursCongestion(time);
		break;
	case oursNoFlowRouting:
		cmpoursNoFlowRouting(time);
		break;
	}
	return true;
}
