#include "Game.h"
#include "Menu.h"

Location* Game::locationMaker(Area input)
{
	switch (input) {
		case TOWNCENTER:			return new TownCenter;
		case TOWNHALL:				return new TownHall;
		case TOWNHALLLOBBY:			return new TownHallLobby;
		case THIEFSHOUSE:			return new ThiefsHouse;
		case THIEFSHOUSEINTERIOR:	return new ThiefsHouseInterior;
		default:
			display("Error: locationMaker() was given an invalid location and didn't return anything.  It is very likely that the program will crash if you do anything other than quit right now.\n");
			break;
	}
}

Game::Game() : PC(StartingLocation)
{
	display("\nWelcome to the adventure game!\n\n");
	currentArea = StartingLocation;
	location = locationMaker(StartingLocation);
}

void Game::run()
{	
	while (true) {
		if (Menu::getDisplayActions()) {
			cout << endl;
			location->displayActions(PC);
		}
		
		cout << endl <<"What will you do?\n";
		getline(cin, input);
		cout << endl;
		
		if (input == "quit" || input == "0") {
			cout << "Goodbye!\n";
			break;
		} else if (input == "menu") {
			Menu menu(PC);
			menu.pauseMenu();
		} else {
			location->getCommand(input, PC);
			if (PC.isDead())
				break; // Each deadly action should have its own output, so there's no need to define one for here.
			if (currentArea != PC.getCurrentLocation()) {
				currentArea = PC.getCurrentLocation();
				delete location;
				location = locationMaker(currentArea);
			}
		}
	}
	
	cout << endl;
}