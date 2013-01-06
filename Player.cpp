#include "Player.h"

Player::Player(Area currentLocationIn)
{
	currentLocation = currentLocationIn;
	isAlive = true;
}

void Player::addToInventory(Item input, uint quantity)
{
	for (uint i = 0; i < quantity; i++)
		Inventory.insert(pair<string, Item> (input.getName(), input));
}

Item Player::getItem(string name) const
{
	if (isInInventory(name))
		return Inventory.find(name)->second;
	else {
		display("Error: getItem() given input on an item that wasn't in the inventory.\n");
		return ERRORITEM;
	}
}

bool Player::isInInventory(Item input) const
{
	if (numInInventory(input) > 0)
		return true;
	else
		return false;
}

bool Player::isInInventory(string name) const
{
	if (numInInventory(name) > 0)
		return true;
	else
		return false;
}

uint Player::numInInventory(Item input) const
{
	return (uint) Inventory.count(input.getName());
}

uint Player::numInInventory(string name) const
{
	return (uint) Inventory.count(name);
}

int Player::removeFromInventory(Item input, uint quantity)
{
	uint count = (uint) numInInventory(input);
	if (count < quantity)
		return -1;
	else {
		multimap<string, Item, ItemComp>::iterator It = Inventory.lower_bound(input.getName());
		multimap<string, Item, ItemComp>::iterator ItEnd = It;
		for (uint i = 0; i < quantity; i++) {
			ItEnd++;
		}
		Inventory.erase(It, ItEnd);
		
		return (count - quantity);
	}
}

int Player::removeFromInventory(string name, uint quantity)
{
	uint count = (uint) numInInventory(name);
	if (count < quantity)
		return -1;
	else {
		multimap<string, Item, ItemComp>::iterator It = Inventory.lower_bound(name);
		multimap<string, Item, ItemComp>::iterator ItEnd = It;
		for (uint i = 0; i < quantity; i++) {
			ItEnd++;
		}
		Inventory.erase(It, ItEnd);
		
		return (count - quantity);
	}
}

string Player::inventoryToString() const
{	
	if (Inventory.empty())
		return " empty inventory\n";
	
	stringstream output;
	const uint width = UtilitiesOptions::getScreenWidth();
	multimap<string, Item, ItemComp>::const_iterator it;
	int i, quantity;

	for (it = Inventory.begin() ; it != Inventory.end(); it++) {
		const string lastItem = it->first;
		
		quantity = 0; // This block counts the number of repeats by iterating through the map.  It leaves the iterator on the last copy of the item currently being processed.
		while (it != Inventory.end()) {
			if (it->first == lastItem) {
				quantity++;
				it++;
			} else
				break;
		}
		it--;
		
		output << ' ' << truncateText(it->first, width - 1, quantity) << '\n';
		if (UtilitiesOptions::getDisplayItemDescriptions())
			output << "   " << truncateText((it->second).getDescription(), width - 3) << '\n';
	}
	
	return output.str();
}

ostream& operator<<(ostream &output, Player &input)
{
	output << input.currentLocation << '\n';
	
	multimap<string, Item, ItemComp>::const_iterator it;
	for (it = (input.Inventory).begin() ; it != (input.Inventory).end(); it++)
		output << (it->second).getName() << '\n' << (it->second).isUnique() << '\n' << (it->second).getDescription() << '\n';
	output << "end_of_inventory\n"; 
}

ifstream& operator>>(ifstream &inputFile, Player &input)
{
	int tempArea;
	inputFile >> tempArea;
	input.currentLocation = (Area) tempArea;
	inputFile.ignore(1);
	
	string tempName, tempDescription;
	int tempUnique;
	getline(inputFile, tempName);
	while (tempName != "end_of_inventory") {
		inputFile >> tempUnique;
		inputFile.ignore(1);
		getline(inputFile, tempDescription);
		input.addToInventory(Item(tempName, tempDescription, tempUnique));
		getline(inputFile, tempName);
	}
}