#include "Game.h"
#include "Menu.h"

#define TEMPAREAS \
UtilitiesOptions tempUO; \
Menu tempM(PC); \
TownCenter temp1; \
TownHall temp2; \
TownHallLobby temp3; \
ThiefsHouse temp4; \
ThiefsHouseInterior temp5; \

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

Game::Game() : PC(StartingLocation) {}

void Game::run()
{
	int selection = 1;
	string filename, tester;
	ifstream testStream;
	
	display("\nWelcome to the adventure game!\n");
	
	while(selection != 0) {
		display("\nWhat will you do?\n 1. New game\n 2. Load game\n 0. Quit game\n");
		selection = getSelection();
		switch (selection) {
			case 1:
				PC = Player(StartingLocation);
				cout << endl;
				playGame();
				break;
			case 0:
				break;
			case 2:
				display("What is the name of your save file?\n");
				getline(cin, filename);
				
				testStream.open(filename.c_str());
				getline(testStream, tester);
				if (tester != "start_save_file") {
					stringstream output;
					output << "Error:  " << filename << " is not the name of a valid save file.\n";
					display(output.str());
					break;
				}
				testStream.close();
				
				loadGame(filename, PC);
				playGame(filename);
				
				break;
			default:
				display("Invalid selection.  Try again.\n");
				break;
		}
	}
	display("\nGood bye!  Thanks for playing!\n\n");
}

void Game::loadGame(string filename, Player &PC)
{
	ifstream file(filename.c_str());
	
	string tempString;
	getline(file, tempString); // clears the "start_save_file"
	
	bool tempBool;
	file >> tempBool;
	Location::setIsDay(tempBool);
		
	file.ignore(1);

	file >> PC;
	
	TEMPAREAS
	
	file >> tempUO;
	file >> tempM;
	
	file >> temp1 >> temp2 >> temp3 >> temp4 >> temp5;
}

void Game::saveGame(string filename, Player &PC)
{
	ofstream file(filename.c_str());
	file << "start_save_file\n";
	file << Location::getIsDay() << '\n';
	
	file << PC;
	
	TEMPAREAS
	
	file << tempUO;
	file << tempM;
	
	file << temp1 << temp2 << temp3 << temp4 << temp5;
	file << "end_of_save_file\n";
}
	

void Game::playGame(string filename)
{	
	display("Your adventure starts.  Keep your wits about you, young adventureer.\n\n");
	
	Location *location = locationMaker(PC.getCurrentLocation());
	string output = areaToString(PC.getCurrentLocation());
	output += '\n';
	display(output);
		
	if(Menu::getDisplayDescription())
		location->displayDescription();
	
	string input;

	while (true) {
		if (Menu::getDisplayActions()) {
			cout << endl;
			location->displayActions(PC);
		}
		
		cout << endl <<"What will you do?\n";
		getline(cin, input);
		cout << endl;
		
		if (input == "quit" || input == "0") {
			cout << "And thus your adventure comes to a close for the day.\n";
			break;
		} else if (input == "menu") {
			Menu menu(PC);
			menu.pauseMenu();
		} else if (input == "save") { 
			while (filename == "") {
				display("Enter a name for your save file:\n");
				getline(cin, filename);
				if (filename == "")
					display("Invalid name.  Try again.\n");
			}
			saveGame(filename, PC);
			display("Saved successfully.\n");
		} else {
			location->getCommand(input, PC);
			if (PC.isDead())
				break; // Each deadly action should have its own output, so there's no need to define one for here.
			if (location->getArea() != PC.getCurrentLocation()) {
				delete location;
				location = locationMaker(PC.getCurrentLocation());
				
				string output = areaToString(PC.getCurrentLocation());
				output += '\n';
				display(output);
				
				if(Menu::getDisplayDescription())
					location->displayDescription();
			}
		}
	}
}