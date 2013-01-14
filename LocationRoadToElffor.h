#ifndef LOCATIONROADTOELFFOR_H
#define LOCATIONROADTOELFFOR_H

#include "Globals.h"
#include "Utilities.h"
#include "Location.h"

class RoadToElffor : public Location {
	STANDARDREGIONDECLARATIONS
protected:
	RoadToElffor(Area input, Player &PCIn) : Location(input, PCIn) {}
	static bool BattleFought;
};

class RoadToElfforA : public RoadToElffor {
	STANDARDLOCATIONDECLARATIONS
public:
	RoadToElfforA(Player &PCIn) : RoadToElffor(ROADTOELFFORA, PCIn) {}
};

#endif