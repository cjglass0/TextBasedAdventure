#ifndef GAME_H
#define GAME_H

#include "Globals.h"
#include "Utilities.h"
#include "Locations.h"

class Game {
private:
	Player PC;
	
	Location *locationMaker(Area input);
	void loadGame(string filename, Player &PC);
	void saveGame(string filename, Player &PC);
	void playGame(string filename = "");
public:
	Game();
	void run();
};

#endif