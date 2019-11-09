#include "Game.h"
#include "Menu.h"

Game::Game() : PC(StartingLocation), LocationVar(PC, WorldVars)
{
	saveDefaultData();
}

void Game::initializeAllLocations() {
	//Create a separate Location for every place in the game that has one
	//	Including their predefined actions
	//Add all of these to the allAreas vector
	//enum Area {TERMINATE = -1, AREASTARTMARKER, ELFFORMYHOUSEINTERIOR, ELFFORMYHOUSE, ELFFORGATE, ELFFORTAVERN, ELFFORTAVERNINTERIOR, ROADTOELFFORA, AREAENDMARKER};

	Location* location_ELFFORMYHOUSEINTERIOR = new Location(PC, WorldVars);
	location_ELFFORMYHOUSEINTERIOR->setLocationValue(ELFFORMYHOUSEINTERIOR);
	location_ELFFORMYHOUSEINTERIOR->addConnectedLocation(ELFFORMYHOUSE);
	location_ELFFORMYHOUSEINTERIOR->setActions();
	addToAreas(location_ELFFORMYHOUSEINTERIOR);

	Location* location_ELFFORMYHOUSE = new Location(PC, WorldVars);
	location_ELFFORMYHOUSE->setLocationValue(ELFFORMYHOUSE);
	location_ELFFORMYHOUSE->addConnectedLocation(ELFFORMYHOUSEINTERIOR);
	location_ELFFORMYHOUSE->addConnectedLocation(ELFFORGATE);
	location_ELFFORMYHOUSE->addConnectedLocation(ELFFORTAVERN);
	location_ELFFORMYHOUSE->setActions();
	addToAreas(location_ELFFORMYHOUSE);

	Location* location_ELFFORTAVERN = new Location(PC, WorldVars);
	location_ELFFORTAVERN->setLocationValue(ELFFORTAVERN);
	location_ELFFORTAVERN->addConnectedLocation(ELFFORMYHOUSE);
	location_ELFFORTAVERN->addConnectedLocation(ELFFORTAVERNINTERIOR);
	location_ELFFORTAVERN->setActions();
	addToAreas(location_ELFFORTAVERN);

	Location* location_ELFFORTAVERNINTERIOR = new Location(PC, WorldVars);
	location_ELFFORTAVERNINTERIOR->setLocationValue(ELFFORTAVERNINTERIOR);
	location_ELFFORTAVERNINTERIOR->addConnectedLocation(ELFFORTAVERN);
	location_ELFFORTAVERNINTERIOR->setActions();
	addToAreas(location_ELFFORTAVERNINTERIOR);

	Location* location_ELFFORGATE = new Location(PC, WorldVars);
	location_ELFFORGATE->setLocationValue(ELFFORGATE);
	location_ELFFORGATE->addConnectedLocation(ELFFORMYHOUSE);
	location_ELFFORGATE->addConnectedLocation(ELFFORTAVERN);
	location_ELFFORGATE->addConnectedLocation(ROADTOELFFORA);
	location_ELFFORGATE->setActions();
	addToAreas(location_ELFFORGATE);

	Location* location_ROADTOELFFORA = new Location(PC, WorldVars);
	location_ROADTOELFFORA->setLocationValue(ROADTOELFFORA);
	location_ROADTOELFFORA->addConnectedLocation(ELFFORGATE);
	location_ROADTOELFFORA->addConnectedLocation(ELFFORTAVERN);
	location_ROADTOELFFORA->addConnectedLocation(ROADTOELFFORA);
	location_ROADTOELFFORA->setActions();
	addToAreas(location_ROADTOELFFORA);
}

void Game::addToAreas(Location* loc) {
	allAreas.insert(std::pair<Area, Location*>(loc->getLocationValue(), loc));
}

void Game::run()
{
	int selection;
	string filename, tester;
	ifstream testStream;
	
	display("\nWelcome to the adventure game!\n");
	
	do {
		display("\nWhat will you do? (enter the number corresponding to your selection)\n 1. New game\n 2. Load game\n 0. Quit game\n");
		selection = getSelection();
		switch (selection) {
			case 1:
				cout << '\n';
				if (loadDefaultData() == OK)
					playGame();
				break;
			case 0:
				break;
			case 2:
				display("\nWhat is the name of your save file? (press enter to cancel)\n");
				getline(cin, filename);
				
				testStream.open(filename.c_str());
				getline(testStream, tester);
				if (filename != "") {
					if (tester != "start_save_file") {
						stringstream output;
						output << "\nSorry, " << filename << " is not the name of a valid save file.  Try again.\n";
						display(output.str());
						selection = -1;
						break;
					}
					testStream.close();
				
					if (loadGame(filename) == ERROR)
						cout << "Error: something went wrong with loadGame().\n";
					else {
						cout << '\n';
						playGame(filename);
					}
				}
				break;
			default:
				display("Invalid selection. Try again.\n");
				break;
		}
	} while (selection != 0);
	
	display("\nGood bye! Thanks for playing!\n\n");
}

#define SAVEDATABODY(file) \
	file << "start_save_file\n"; \
	file << UtilitiesOptions::saveData() << PC.saveData() << Menu::saveData() << WorldVars.saveData(); \
	file << "end_of_save_file\n";

void Game::saveData(string filename)
{
	ofstream file(filename.c_str());
	SAVEDATABODY(file)
	file.close();
}

void Game::saveDefaultData()
{
	stringstream strstr;
	SAVEDATABODY(strstr)
	defaultData = strstr.str();
}

status Game::saveGame(string &filename)
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
				
				saveData(filename);
				display("\nSaved successfully (new file written).\n");
				return OK;
			} else {
				string teststring;
				
				getline(testfile, teststring);
				testfile.close();
				
				if (teststring == "start_save_file") {
					
					stringstream tempstrstr;
					tempstrstr << "\n\"" << filename << "\" already exists as a save file. Would you like to overwrite it?\n 1. Yes\n 0. No\n";
					display(tempstrstr.str());
					
					int selection = getSelection();
					if (selection == 1) {
						saveData(filename);
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
		saveData(filename);
		
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
	} while (tempString[0] != ENDMARKER);

#define LOADDATABODY(file, FUNCTIONNAME) \
	string tempString; \
	getline(file, tempString); \
	\
	if (tempString != "start_save_file") { \
		cout << "Error: " << FUNCTIONNAME << " given improper save file.\n"; \
		return ERROR; \
	} \
	\
	stringstream input; \
	GETDATAFORLOAD \
	UtilitiesOptions::loadData(input.str()); \
	GETDATAFORLOAD \
	PC = Player(StartingLocation); \
	PC.loadData(input.str()); \
	GETDATAFORLOAD \
	Menu::loadData(input.str()); \
	GETDATAFORLOAD \
	WorldVars.loadData(input.str()); \
	getline(file, tempString); \
	if (tempString != "end_of_save_file") \
		cout << "Error:  a load function didn't reach the end of the savefile.\n"; \
	return OK;
	
status Game::loadGame(string filename)
{
	ifstream file(filename.c_str());
	LOADDATABODY(file, "loadGame")
	file.close();
}

status Game::loadDefaultData()
{
	stringstream file(defaultData);
	LOADDATABODY(file, "loadDefaultData")
}

void Game::playGame(string filename)
{	
	display("Your adventure starts. Keep your wits about you, young adventureer.\n\n");
	
	lastLocation = AREASTARTMARKER; // Set equal to a dummy value of the num so an area's name/description is always displayed at the start of a new game.
	string input;
	int savedOnLastTurn = 1;
	
	while (true) {
		if (lastLocation != PC.getCurrentLocation()) {
			if(Menu::getDisplayDescription())
				LocationVar.displayDescription();
			else {
				display(areaToString(PC.getCurrentLocation()));
				cout << '\n';
			}
		}
		lastLocation = PC.getCurrentLocation();

		if (Menu::getDisplayActions()) {
			cout << '\n';
			LocationVar.displayActions();
		}
		
		cout << "\nWhat will you do?\n";
		getline(cin, input);
		cout << '\n';
		
		//RE: Case-insensitive research
		//	This section is important
		//	input -> this variable can be sanitized to lower case before any reads are done to it
		//	THEN, any evaluations of its content need to be done expecting the data to be lower case
		//	Where do these evaluations take place?
		//		See: LocationVar.getCommand(input)
		//	--- UPDATE ---
		//	Action header updated to automatically transform the game's command registry to only contain lower case actions
		//	Only thing left is to convert the input to lower case, which is trivial
		//	The implementation's expected behaviour has been validated
		//	Test Case 1: Registered command "observe"
		//		User Input "observe"
		//			Expected Result: Success, as defined by [Location's observation text displayed, indicating the correct function being chosen]
		//			Observed Result:  Success
		//		User Input "OBSERVE"
		//			Expected Result: Success, see above
		//			Observed Result:  Success
		//		User Input "oBsErVe"
		//			Expected Result: Success, see above
		//			Observed Result:  Success
		//	Test Case 2: Registered command "OBSERVE"
		//		User Input "observe"
		//			Expected Result: Success, as defined by [Location's observation text displayed, indicating the correct function being chosen]
		//			Observed Result:  Success
		//		User Input "OBSERVE"
		//			Expected Result: Success, see above
		//			Observed Result:  Success
		//		User Input "oBsErVe"
		//			Expected Result: Success, see above
		//			Observed Result:  Success
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		if (input == "quit" || input == "0") {
			bool quitIt = false;
			
			if (savedOnLastTurn > 0) {
				quitIt = true;
			} else {
				display("Would you like to save before you quit?\n 1. Yes\n 0. No\n");
				int selection = getSelection();
				if (selection == 1) {
					if (saveGame(filename) == OK)
						quitIt = true;
				} else if (selection == 0)
					quitIt = true;
			}
			if (quitIt) {
				if (savedOnLastTurn <= 0)
					cout << '\n';
				display("And thus your adventure comes to an end for the day.\n");
				return;
			}
		} else if (input == "menu") {
			Menu menu(PC);
			menu.pauseMenu();
		} else if (input == "save") {
			if (saveGame(filename) == OK)
				savedOnLastTurn = 2;
		}
		else if (input == "map") {
			//display map
			display("You look at your map.\n");

		}
		else {
			LocationVar.getCommand(input);
			if ((PC.isDead()) || (PC.getCurrentLocation() == TERMINATE)) {
				enterToContinue(); // Each deadly action should have its own output, so there's no need to define one for here.
				break;
			}
		}
		
		if (savedOnLastTurn > 0)
			--savedOnLastTurn;
	}
}