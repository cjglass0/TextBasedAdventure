#include "Locations.h"
#include "Menu.h"

string areaToString(Area input)
{
	switch (input) {
		case TOWNCENTER:			return "Town Center";
		case TOWNHALL:				return "Town Hall";
		case TOWNHALLLOBBY:			return "Town Hall Lobby";
		case THIEFSHOUSE:			return "Thief's House";
		case THIEFSHOUSEINTERIOR:	return "Thief's House Interior";
		default:
			return "Error: areaToString() received improper input.\n";
	}
}

Location::Location(Area input) : here(input)
{
	string output = areaToString(input);
	output += '\n';
	display(output);
}

void Location::getCommand(string input, Player &PC)
{
	if (input == "actions") {
		if (Menu::getDisplayActions() == false)
			displayActions(PC);
	} else if (input == "observe")
		displayDescription();
	else if ((input == "wait until day") || (input == "wait until night"))
		processWait(input);
	else {
		if (processCommand(input, PC) == ERROR) {
			displayUnknownCommand();
		}
	}
}

bool Location::IsDay = true;

// Put a space before all displayed actions.
void Location::displayActions(Player &PC)
{
	stringstream output;
	output << "Your possible actions are:\n observe\n" << getActions(PC) << (IsDay ? " wait until night\n" : " wait until day\n") << " menu\n quit\n";
	display(output.str());
}

void Location::displayUnknownCommand()
{
	if (Menu::getDisplayActions())
		display("Whatever that is, you can't do it.\n");
	else
		display("Whatever that is, you can't do it.  Try using the \"actions\" command.\n");
}

void Location::processWait(string input)
{
	if (input == "wait until day") {
		if (IsDay == false) {
			IsDay = true;
			cout << "You wait until the sun rises.\n";
		} else
			cout << "But it already is day...\n";
	}
	else if (input == "wait until night") {
		if (IsDay == true) {
			IsDay = false;
			cout << "You wait until the sun sets.\n";
		} else
			cout << "But it is already night...\n";
	}
	else
		cout << "Error: processWait() was forced to handle an unknown input.\n";
}
