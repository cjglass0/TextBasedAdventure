#ifndef GAME_H
#define GAME_H

#include "Globals.h"
#include "Utilities.h"
#include "Locations.h"

class Game {
private:
	Player PC;
	string defaultData;
	
	Location *locationMaker(Area input);
	
	void saveDefaultData();
	status loadDefaultData();
	
	status saveGame(string &filename);
	void saveData(string filename);
	status loadGame(string filename);
	void playGame(string filename = "");
public:
	Game();
	void run();
};

#endif