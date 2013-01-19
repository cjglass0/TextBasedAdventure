#ifndef ACTIONS_H
#define ACTIONS_H

#include "Globals.h"
#include "Utilities.h"
#include "Player.h"
#include "WorldVariables.h"

class Action {
public:
	// These variables have been set up like this so I can get the code to compile.  The class's setup might be improved later.
	string command; // This should be constant
	bool showAction; // This and the one below should be private.
	void (*funcPtr)(Player&, WorldVariables&, bool&);
	
	Action(string commandIn, void (*funcPtrIn)(Player&, WorldVariables&, bool&), bool showActionIn = true) : command(commandIn), showAction(showActionIn), funcPtr(funcPtrIn) {}
	bool getShowAction(){return showAction;}
	void callAction(Player &PC, WorldVariables &WorldVars){(*funcPtr)(PC, WorldVars, showAction);}
};

#define FUNCACTION(NAME) void NAME(Player &PC, WorldVariables &WorldVars, bool &showAction) 

FUNCACTION(goToElfforMyHouseInterior);
FUNCACTION(goToElfforMyHouse);
FUNCACTION(goToElfforTavern);
FUNCACTION(goToElfforTavernInterior);
FUNCACTION(goToElfforGate);
FUNCACTION(goToRoadToElfforA);

FUNCACTION(waitUntilDay);
FUNCACTION(waitUntilNight);

FUNCACTION(observeAction);

FUNCACTION(observeElfforMyHouseInterior);
FUNCACTION(observeElfforMyHouse);
FUNCACTION(observeElfforGate);
FUNCACTION(observeElfforTavern);
FUNCACTION(observeElfforTavernInterior);
FUNCACTION(observeRoadToElfforA);

FUNCACTION(ElfforHouseSleepInBed);
FUNCACTION(ElfforHouseWaitUntilDay);
FUNCACTION(ElfforHouseWaitUntilNight);

FUNCACTION(ElfforReadSign);

FUNCACTION(ElfforEnterTavern);

FUNCACTION(ElfforTalkToTrent);
FUNCACTION(ElfforTalktoNina);
FUNCACTION(ElfforTavernWaitUntilDay);
FUNCACTION(ElfforTavernWaitUntilNight);

FUNCACTION(EnterElffor);
FUNCACTION(RoadToElfforGoDownPath);

#endif