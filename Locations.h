#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "Globals.h"
#include "Utilities.h"
#include "Menu.h"
#include "Location.h"

#define STANDARDDECLARATIONS(CLASSNAME, HERE) \
private: \
	static string description;\
public: \
	CLASSNAME() : Location(HERE) {} \
	void displayDescription(); \
	status processCommand(string input, Player &PC); \
	string getActions(Player &PC); \
	string saveData(); \
	void loadData(string input);

class TownCenter : public Location {
	STANDARDDECLARATIONS(TownCenter, TOWNCENTER)
};

class TownHall : public Location {
	STANDARDDECLARATIONS(TownHall, TOWNHALL)
private:
	static bool DoorUnlocked;
};

class TownHallLobby : public Location {
	STANDARDDECLARATIONS(TownHallLobby, TOWNHALLLOBBY)
private:
	static bool TreasuryChestSearched;
};

class ThiefsHouse : public Location {
	STANDARDDECLARATIONS(ThiefsHouse, THIEFSHOUSE)
};

class ThiefsHouseInterior : public Location {
	STANDARDDECLARATIONS(ThiefsHouseInterior, THIEFSHOUSEINTERIOR)
private:
	static bool ThiefSawYou;
	void processWait(string input);
};

#endif