#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Globals.h"
#include "Utilities.h"
#include "Player.h"

class Menu {
private:
	Player &PC;
	static bool DisplayDescription;
	static bool DisplayActions;
	
	void optionsMenu();
	void inventoryMenu();
public:
	Menu(Player &input);
	void pauseMenu();
	
	static bool getDisplayDescription(){return DisplayDescription;}
	static bool getDisplayActions(){return DisplayActions;}
	
	friend ostream& operator<<(ostream &output, Menu &input);
	friend ifstream& operator>>(ifstream &inputFile, Menu &input);
};

#endif