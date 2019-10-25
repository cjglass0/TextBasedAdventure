#ifndef PLAYER_H
#define PLAYER_H

#include "Globals.h"
#include "Utilities.h"
#include "Item.h"

struct ItemComp {
	bool operator() (const string& leftComp, const string& rightComp) const {return stringComp(leftComp, rightComp) == 1;}
};

//RE: Character Progression Report
//	Adding new properties to the Player class is simple, it is just a matter of deciding which ones to add and then being able to access them
//	One approach would be to have separate fields for each bit of information, for example:
//		int health = 100, stamina = 100, mana = 100;
//	While simple, each field will need to be accessed somehow, and having a ton of fields that all together denote player state might get unwieldy
//		That said, I think no matter what approach we will need an accessor for each field.  The debate is on how to organize
//	Another approach would be to aggregate related data together in a struct or its own class
//		For example, suppose we have a "Resource Class" that contains fields for health, stamina, and mana
//		The player might not be the only entity that makes use of such primary data, for example enemies might be able to use it too
//		All entities can contain a field for a Resource Object and could implement an interface to get all of the functions
//			Or the entities could extend the Resource Class to get all of the functions
//	By keeping related stats together, any changes to implementation are abstracted away and entity-specific behaviour can still be layered in
//	---------
//	In terms of what data could be relevant, here is a list:
/*		-HP (max & curr), SP (max & curr), MP (max & curr)
		-Strength, Constitution, Defense, Dexterity
		-Intelligence, Charisma, Wisdom, Willpower, Perception, Luck
		-Level, experience, gold/money
		-Active Skills (a list of abilities the player has unlocked as they level up)
		-Passive Skills (a list of abilities that apply all the time and cannot be turned off.  Might affect success rates and stuff like that)
		-Class (Fighter, Mage, etc), Race (Human, Elf, etc)
*///---------
//	As alluded in the list, this kind of progression needs to be measured.  Levels and experience are the best way to keep track of this
//	So, an entity should have a Level, keep track of its experience, and know its experience curve
//	No matter what implementation for this progression, this class will need some functions to expose the state to outsiders
class Player {
private:
	bool isAlive;
	Area currentLocation;
	multimap<string, Item, ItemComp> Inventory;
public:
	Player(Area currentLocationIn);
	
	Area getCurrentLocation(){return currentLocation;}
	void setCurrentLocation(Area input){currentLocation = input;}
	bool isDead(){return !isAlive;}
	void killPlayer(){isAlive = false;}
	
	void addToInventory(Item input, uint quantity = 1);
	Item getItem(string name) const;
	bool isInInventory(Item input) const;
	bool isInInventory(string name) const;
	uint numInInventory(Item input) const; // returns the number of such objects in the inventory
	uint numInInventory(string name) const;
	bool emptyInventory() const {return Inventory.empty();}
	int removeFromInventory(Item input, uint quantity = 1);// returns the number of such objects remaining in the inventory.  Returns -1 if nothing removed (i.e. if quantity > count).
	int removeFromInventory(string name, uint quantity = 1);
	string inventoryToString() const;
	
	string saveData();
	void loadData(string input);
};

#endif