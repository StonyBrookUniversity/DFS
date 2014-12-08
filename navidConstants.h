#ifndef NAVIDCONSTANTS_H
#define NAVIDCONSTANTS_H

#define SIMULATION_CLOCK_PER_SECOND 1000000000000
#define SIMULATION_CLOCK_PER_MICRO_SECOND 1000000
#define SM_ACTINATION_TIME 2000000000
#define CTHROUGH_ACTINATION_TIME 2000000000
#define TDBEAM_ACTINATION_TIME 2000000000
#define MAX_NEXT_HOP 48
#define TDBEAM_TRESHOLD 8
#define TDBEAM_NET_TRESHOLD 2
#define TDBEAM_INDIVISUAL_TRESHOLD 4
#define CTHROUGH_INDIVISUAL_TRESHOLD 1
#define PRIORITY_SHIFT 2000000000
#define FLOW_IDLE_TIMEOUT 1000*SIMULATION_CLOCK_PER_MICRO_SECOND

static const unsigned long long int PRIODICTIME_CTHROUGH=((unsigned long long int)500*(unsigned long long int)SIMULATION_CLOCK_PER_MICRO_SECOND);
static const unsigned long long int PRIODICTIME_FIRFLY=((unsigned long long int)1000000*(unsigned long long int)SIMULATION_CLOCK_PER_MICRO_SECOND);


//#define CheckConsistancyMacro
//#define CheckRoutingMacro

//#define CheckConsistMacro





typedef long long int Sim_Timer;
enum trafficAlgorithm {
	tDBeam,
	cThrough,
	oursCongestion,
	oursNoFlowRouting,
	jellyFish,
	ourPriodicReconfig,
	ourCombined,
	fatTree,
};

#endif

