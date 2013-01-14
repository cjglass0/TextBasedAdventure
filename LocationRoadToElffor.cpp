#include "LocationRoadToElffor.h"

// Array initialization would look like bool RoadToElffor::BattlesFought[] = {false, false}; (assumedly)
bool RoadToElffor::BattleFought = false;

string RoadToElffor::saveRegionData()
{
	stringstream output;
	output << BattleFought << '\n' << ENDMARKER << '\n';
	return output.str();	
}

void RoadToElffor::loadRegionData(string input)
{
	stringstream strstr(input);
	strstr >> BattleFought;
	
	strstr.ignore(1);
	LOADDATACHECK("RoadToElffor")
}

/*
 *		Road to Elffor: region A
 */

void RoadToElfforA::displayDescription()
{
	string output = "Outside of the gate to Elffor.  There's a path the leads into some dark woods.  ";
	if (! BattleFought)
		output += "There's a rustling coming from in the trees.  ";
	else
		output += "All is relatively still.  ";
	if (IsDay)
		output += "It is daytime.\n";
	else {
		if (PC.isInInventory(LANTERN))
			output += "It is nighttime.\n";
		else
			output += "It is nighttime, and you can see that it's hard to see in the woods.\n";
	}
	display(output);
}

status RoadToElfforA::processCommand(string input)
{
	if (input == "enter Elffor") {
		PC.setCurrentLocation(ELFFORTOWNGATE);
		BattleFought = false;
	} else if (input == "go down path") {
		if (BattleFought)
			display("This is where you'd move to a new area.\n"); // temp code
		else {
			if ((! IsDay) && (! PC.isInInventory(LANTERN))) {
				display("In the dark of the night, made only more impregnable by the thick woods, you could only hear the wolf moving through the brush.\
  By the time you saw him, he was already at your throat.\n");
				PC.killPlayer();
				enterToContinue();
			} else if (! PC.isInInventory(RUSTYSWORD)) {
				display("A wolf leaps out from the brush and sprints towards you.  Alas, with no means of defending yourself, you become its next dinner.\n");
				PC.killPlayer();
			} else {
				display("A wolf leaps out from the brush, intent on making you its dinner.  Seeing the wolf coming at you, you slay the beast with your sword.\
  The path is now safe to walk.\n");
				BattleFought = true;
			}
		}
	} else
		return ERROR;
	return OK;
}

string RoadToElfforA::getActions()
{
	return " enter Elffor\n go down path\n";
}

string RoadToElfforA::saveData()
{
	DEFAULTLOCATIONSAVEBODY
}

void RoadToElfforA::loadData(string input)
{
	DEFAULTLOCATIONLOADBODY
}
