#include "Game.h"
#include "Menu.h"

Location* Game::locationMaker(Area input)
{
	switch (input) {
		case TOWNCENTER:	return new TownCenter;
		case TOWNHALL:	return new TownHall;
		case TOWNHALLLOBBY:	return new TownHallLobby;
		case THIEFSHOUSE:	return new ThiefsHouse;
		case THIEFSHOUSEINTERIOR:	return new ThiefsHouseInterior;
		default:
			cout << "Error: locationMaker() was given an invalid location and didn't return anything. It is very likely that the program will crash if you do anything other than quit right now.\n";
			break;
	}
}

Game::Game() : PC(StartingLocation) {}

void Game::run()
{
	int selection = -1;
	string filename, tester;
	ifstream testStream;
	
	display("\nWelcome to the adventure game!\n");
	
	while ((selection < 0) || (selection > 2)) {
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
				display("\nWhat is the name of your save file?\n");
				getline(cin, filename);
				
				testStream.open(filename.c_str());
				getline(testStream, tester);
				if (tester != "start_save_file") {
					stringstream output;
					output << "Sorry, " << filename << " is not the name of a valid save file. Try again.\n";
					display(output.str());
					selection = -1;
					break;
				}
				testStream.close();
				
				if (loadGame(filename, PC) == ERROR)
					cout << "Error: something went wrong with loadGame().\n";
				else
					cout << endl;
				playGame(filename);
				
				break;
			default:
				display("Invalid selection. Try again.\n");
				break;
		}
	}
	display("\nGood bye! Thanks for playing!\n\n");
}

void Game::saveData(string filename, Player &PC)
{
	ofstream file(filename.c_str());
	file << "start_save_file\n";
	file << UtilitiesOptions::saveData() << PC.saveData() << Menu::saveData() << Location::saveLocationData();	
	
	Location *temp;
	for (int i = ((int) AREASTARTMARKER) + 1; i < ((int) AREAENDMARKER); i++) {
		temp = locationMaker((Area) i);
		file << temp->saveData();
		delete temp;
	}
	
	file << "end_of_save_file\n";
}

status Game::saveGame(string &filename, Player &PC)
{
	if (filename == "") {
		display("Enter a name for your save file (press enter to cancel process):\n");
		getline(cin, filename);
		if (filename == "") {
			display("No data saved.\n");
			return ERROR;
		}
		else {
			ifstream testfile(filename.c_str());
			
			if (! testfile) {
				testfile.close();
				
				saveData(filename, PC);
				display("\nSaved successfully (new file written).\n");
				return OK;
			} else {
				string teststring;
				
				getline(testfile, teststring);
				testfile.close();
				
				if (teststring == "start_save_file") {
					
					stringstream tempstrstr;
					tempstrstr << "\n\"" << filename << "\" already exists as a save file. Would you like to override it?\n 1. Yes\n 0. No\n";
					display(tempstrstr.str());
					
					int selection = getSelection();
					if (selection == 1) {
						saveData(filename, PC);
						display("\nFile overwritten. Saved successfully.\n");
						return OK;
					} else {
						display("\nFile not overwritten. No data saved.\n");
						filename = "";
						return ERROR;
					}
				} else {
					display("\nThat file already exists, and it's not a save file, so it can't be overwritten. No data saved.\n");
					filename = "";
					return ERROR;
				}
			}
		}
	} else {
		saveData(filename, PC);
		
		stringstream output;
		output << "Saved successfully to file \"" << filename << "\".\n";
		display(output.str());
		
		return OK;
	}
}


#define GETDATAFORLOAD \
input.str(""); \
do { \
getline(file, tempString); \
input << tempString << '\n'; \
} while (tempString[0] != ENDMARKER); \

status Game::loadGame(string filename, Player &PC)
{
	ifstream file(filename.c_str());
	
	string tempString;
	getline(file, tempString);
	
	if (tempString != "start_save_file") {
		cout << "Error: loadGame given improper save file.\n";
		return ERROR;
	}
	
	stringstream input;
	
	GETDATAFORLOAD
	UtilitiesOptions::loadData(input.str());
	
	GETDATAFORLOAD
	PC.loadData(input.str());
	
	GETDATAFORLOAD
	Menu::loadData(input.str());
	
	GETDATAFORLOAD
	Location::loadLocationData(input.str());
	
	Area i = ((Area) (((int) AREASTARTMARKER) + 1));
	Location *tempLocation;
	
	input.str("");
	getline(file, tempString);
	input << tempString << '\n';
	while ((input.str() != "end_of_save_file") && (i < AREAENDMARKER)) {
		while (tempString[0] != ENDMARKER) {
			getline(file, tempString);
			input << tempString << '\n';
		}
		
		tempLocation = locationMaker(i);
		tempLocation->loadData(input.str());
		delete tempLocation;
		
		i = ((Area) (((int) i) + 1));
		
		input.str("");
		getline(file, tempString);
		input << tempString << '\n';
	}
	
	return OK;
}	

void Game::playGame(string filename)
{	
	display("Your adventure starts. Keep your wits about you, young adventureer.\n\n");
	
	Location *location = locationMaker(PC.getCurrentLocation());
	string output = areaToString(PC.getCurrentLocation());
	output += '\n';
	display(output);
	
	if(Menu::getDisplayDescription())
		location->displayDescription();
	
	string input;
	int savedOnLastTurn = 1;
	
	while (true) {
		if (Menu::getDisplayActions()) {
			cout << endl;
			location->displayActions(PC);
		}
		
		cout << endl <<"What will you do?\n";
		getline(cin, input);
		cout << endl;
		
		if (input == "quit" || input == "0") {
			bool quitIt = false;
			
			if (savedOnLastTurn > 0) {
				quitIt = true;
			} else {
				display("Would you like to save before you quit?\n 1. Yes\n 0. No\n");
				int selection = getSelection();
				if (selection == 1) {
					if (saveGame(filename, PC) == OK)
						quitIt = true;
				} else if (selection == 0)
					quitIt = true;
			}
			if (quitIt) {
				if (savedOnLastTurn <= 0)
					cout << '\n';
				display("And thus your adventure comes to a close for the day.\n");
				return;
			}
		} else if (input == "menu") {
			Menu menu(PC);
			menu.pauseMenu();
		} else if (input == "save") {
			if (saveGame(filename, PC) == OK)
				savedOnLastTurn = 2;
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
		
		if (savedOnLastTurn > 0)
			--savedOnLastTurn;
	}
}