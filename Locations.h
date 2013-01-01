#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "Globals.h"
#include "Utilities.h"
#include "Menu.h"
#include "Location.h"

#define STANDARDFUNCTIONS(CLASSNAME, HERE) \
CLASSNAME() : Location(HERE) {if(Menu::getDisplayDescription()) displayDescription();} \
void displayDescription(); \
Area processCommand(string input); \
string getActions();

class TownCenter : public Location {
private:
	static string description;
public:
	STANDARDFUNCTIONS(TownCenter, TOWNCENTER)
};

class TownHall : public Location {
private:
	static string description;
	static bool DoorUnlocked;
public:
	STANDARDFUNCTIONS(TownHall, TOWNHALL)
};

class TownHallLobby : public Location {
private:
	static string description;
	static bool TreasuryChestSearched;
public:
	STANDARDFUNCTIONS(TownHallLobby, TOWNHALLLOBBY)
};
	
class ThiefsHouse : public Location {
private:
	static string description;
public:
	STANDARDFUNCTIONS(ThiefsHouse, THIEFSHOUSE)
};

class ThiefsHouseInterior : public Location {
private:
	static string description;
	static bool ThiefSawYou;
public:
	STANDARDFUNCTIONS(ThiefsHouseInterior, THIEFSHOUSEINTERIOR)
	void processWait(string input);
};

#endif