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
	CLASSNAME() : Location(HERE) {if(Menu::getDisplayDescription()) displayDescription();} \
	void displayDescription(); \
	status processCommand(string input, Player &PC); \
	string getActions(Player &PC); \
	static void setDescription(string input){description = input;} \
	static string getDescription(){return description;}

class TownCenter : public Location {
	STANDARDDECLARATIONS(TownCenter, TOWNCENTER)
};

class TownHall : public Location {
	STANDARDDECLARATIONS(TownHall, TOWNHALL)
private:
	static bool DoorUnlocked;
public:
	static void setDoorUnlocked(bool input){DoorUnlocked = input;}
	static bool getDoorUnlocked(){return DoorUnlocked;}
};

class TownHallLobby : public Location {
	STANDARDDECLARATIONS(TownHallLobby, TOWNHALLLOBBY)
private:
	static bool TreasuryChestSearched;
public:
	static void setTreasuryChestSearched(bool input){TreasuryChestSearched = input;}
	static bool getTreasuryChestSearched(){return TreasuryChestSearched;}
};
	
class ThiefsHouse : public Location {
	STANDARDDECLARATIONS(ThiefsHouse, THIEFSHOUSE)
};

class ThiefsHouseInterior : public Location {
	STANDARDDECLARATIONS(ThiefsHouseInterior, THIEFSHOUSEINTERIOR)
private:
	static bool ThiefSawYou;
public:
	static void setThiefSawYou(bool input){ThiefSawYou = input;}
	static bool getThiefSawYou(){return ThiefSawYou;}
	void processWait(string input);
};

#endif