#ifndef LOCATION_H
#define LOCATION_H

/*	To add a new location:
 *		-add it's name to the Area enum in Globals.h (be sure to add it right before the AREAENDMARKER one, after all the previous areas)
 *		-add it to the definision of areaToString() to string in Utilities.cpp
 *		-other stuff (as of yet undetermined)
 *
 *	To add a new region:
 *		-add a prototype to the proper LocationXXXXX.h file
 *		-define its saveRegionData() and loadRegionData() functions in the proper LocationXXXXX.cpp file
 *		-add calls to the those save and load functions in the SAVEDATABODY and LOADDATABODY macros in Game.cpp
 */

#include "Globals.h"
#include "Utilities.h"
#include "Action.h"

class Location {
private:
	void displayUnknownCommand(); // Displays the error message for when an unknown command is entered.

	WorldVariables &WorldVars;
	Player &PC;
	vector<Action> Actions;
	
	string getActions(); // Returns all possible actions in the Actions vector. Each listed action should start with a space and end with a newline character.
public:
	Location(Player &PCin, WorldVariables &WorldVarsIn);

	Area getArea(){return PC.getCurrentLocation();} // Delete this and replace all calls to it with more appropriate functions.
	void displayActions(); // Displays all possible actions, including those that aren't area specific.
	void getCommand(string input); // Takes input and processCommand function to process it. Returns the area the player ends up in after the command is processed.
	void displayDescription(); // Displays the area specific description.
};

#endif