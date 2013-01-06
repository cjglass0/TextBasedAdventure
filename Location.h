#ifndef LOCATION_H
#define LOCATION_H

#include "Globals.h"
#include "Utilities.h"
#include "Player.h"

class Location {
private:
	virtual status processCommand(string input, Player &PC) = 0; // Processes the user's input string to check it against actions unique to the area. Returns the area the player ends up in afterward.
	void displayUnknownCommand(); // Displays the error message for when an unknown command is entered.
	virtual void processWait(string input); // Called when the player waits until day or night. Can be overriden so that waiting has an effect on the area.
protected:
	const Area here;
	static bool IsDay;
	
	Location(Area input);
	virtual string getActions(Player &PC) = 0; // Displays all possible actions unique to the area. Each listed action should start with a space and end with a newline character.
public:
	Area getArea() const {return here;}
	void displayActions(Player &PC); // Displays all possible actions, including those that aren't area specific.
	void getCommand(string input, Player &PC); // Takes input and uses the virtual processCommand function to process it. Returns the area the player ends up in after the command is processed.
	virtual void displayDescription() = 0; // Displays the area specific description. Each area should have its own static description variable.
	
	static bool getIsDay(){return IsDay;}
	static void setIsDay(bool input){IsDay = input;}
};

#endif