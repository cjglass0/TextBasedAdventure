#include "Action.h"

FUNCACTION(goToElfforMyHouseInterior){PC.setCurrentLocation(ELFFORMYHOUSEINTERIOR);}
FUNCACTION(goToElfforMyHouse){PC.setCurrentLocation(ELFFORMYHOUSE);}
FUNCACTION(goToElfforTavern){PC.setCurrentLocation(ELFFORTAVERN);}
FUNCACTION(goToElfforTavernInterior){PC.setCurrentLocation(ELFFORTAVERNINTERIOR);}
FUNCACTION(goToElfforGate){PC.setCurrentLocation(ELFFORGATE);}
FUNCACTION(goToRoadToElfforA){PC.setCurrentLocation(ROADTOELFFORA);}

FUNCACTION(waitUntilDay)
{
	if (WorldVars.IsDay == false) {
		WorldVars.IsDay = true;
		cout << "You wait until the sun rises.\n";
	} else
		cout << "But it already is day...\n";
}

FUNCACTION(waitUntilNight)
{
	if (WorldVars.IsDay == true) {
		WorldVars.IsDay = false;
		cout << "You wait until the sun sets.\n";
	} else
		cout << "But it is already night...\n";
}


FUNCACTION(observeElfforMyHouseInterior)
{
	string output = "The inside of your house.  It's small, but it's home.  ";
	if (! WorldVars.Elffor.SwordRetrieved)
		output += "Your sword usually hangs on the wall, but it's missing, dust outlining where it used to be.  ";
	else
		output += "Dust outlines the spot on the wall where your sword usually hangs.  ";
	output += "There's a bed you can sleep in.  ";
	output += (WorldVars.IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

FUNCACTION(observeElfforMyHouse)
{
	string output = "Outside of your house.  It's a quaint little place.  You can see the tavern and the gate that leads out of town.  ";
	output += (WorldVars.IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

FUNCACTION(observeElfforGate)
{
	string output =  "The gate that leads out of the town, left open to allow free passage.  There is a sign posted on the side of the gate.  You can see the tavern and your house.  ";
	output += (WorldVars.IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

FUNCACTION(observeElfforTavern)
{
	string output = "Outside of the local tavern, The Infernal Woods, a small building constructed of dark wood.  It's a modest place, but it's well-kept.\
  You can see your house and the gate that leads out of town.  ";
	output += (WorldVars.IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

FUNCACTION(observeElfforTavernInterior)
{
	stringstream output;
	if (WorldVars.IsDay) {
		output << "Inside The Infernal Woods.  Trent, the bartender, is ";
		output << (WorldVars.Elffor.SwordRetrieved ? "standing behind the bar.  " : "waving at you, trying to attract your attention.  ");
		output << "Nina is sitting at the bar, sipping a brew.  ";
	} else
		output << "There's no one inside, as the place is closed.  ";
	output << (WorldVars.IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output.str());
}

FUNCACTION(observeRoadToElfforA)
{
	string output = "Outside of the gate to Elffor.  There's a path the leads into some dark woods.  ";
	if (! WorldVars.RoadToElffor.BattleFought)
		output += "There's a rustling coming from in the trees.  ";
	else
		output += "All is relatively still.  ";
	if (WorldVars.IsDay)
		output += "It is daytime.\n";
	else {
		if (PC.isInInventory(LANTERN))
			output += "It is nighttime.\n";
		else
			output += "It is nighttime, and you can see that it's hard to see in the woods.\n";
	}
	display(output);
}

FUNCACTION(ElfforHouseSleepInBed)
{
	if (WorldVars.IsDay) {
		display("You lie in bed in a state of half-sleep, dreaming vividly and just feeling very relaxed.  When you finally force yourself out a bed, night has arrived.\n");
		WorldVars.IsDay = false;
	} else {
		display("You get a good night's rest, waking up with boundless energy, ready to greet the new day.\n");
		WorldVars.IsDay = true;
	}
}

FUNCACTION(ElfforHouseWaitUntilDay)
{
	if (WorldVars.IsDay == false) {
		display("But why just wait when you can sleep in your comfy bed?\n");
	} else
		display("But it already is day...\n");
}

FUNCACTION(ElfforHouseWaitUntilNight)
{
	if (WorldVars.IsDay == true) {
		display("But why just wait when you can sleep in your comfy bed?\n");
	} else
		display("But it is already night...\n");
}

FUNCACTION(ElfforReadSign)
{
	display("WARNING:\nWild wolves have been spotted roaming outside of the town fence.  They will attack unprotected travelers.\
  If you are travelling alone, bring something to defend yourself with.\n");
	enterToContinue();
}

FUNCACTION(ElfforEnterTavern)
{
	if (WorldVars.IsDay)
		PC.setCurrentLocation(ELFFORTAVERNINTERIOR);
	else
		display("The tavern door is locked.\n");
}

FUNCACTION(ElfforTalkToTrent)
{
	if (WorldVars.Elffor.SwordRetrieved) {
		display("\"Is life treating you well, friend?  I certainly hope it is.\"\n");
	} else {
		display("\"I'm glad you popped in!  You left something here last night.\"\n\nTrent hands you your sword.\n");
		PC.addToInventory(RUSTYSWORD);
		WorldVars.Elffor.SwordRetrieved = true;
		enterToContinue();
		display("\n\"You going somewhere?  You'll be needing that, then.  I hear we've got wolves in our midst.\"\n");
		enterToContinue();
		display("\n\"Bah!  Wolves, you say?\" Nina shouts from her stool.  \"We haven't had a wolf problem in years, not since I showed them what's what!  The lad'll be fine!\"\n");
		enterToContinue();
		display("\n\"You need to get out of the tavern more, Nina.  These aren't the times they used to be.\"\n");
		enterToContinue();
		display("\nTrent turns to face you.  \"Either way, good to have your sword back, eh, friend?\"\n");
		enterToContinue();
	}
}

FUNCACTION(ElfforTalktoNina)
{
	if (! WorldVars.Elffor.SwordRetrieved)
		display("\"How ye be these days, lad?\"\n");
	else {
		if (! WorldVars.Elffor.NinaConversationHad) {
			display("\"Trent's just a worry-wort.  You were quite the fighter in your day, if I recall correctly.\"\n");
			enterToContinue();
			display("\n\"Your recall isn't what it used to be, Nina.\"\n");
			enterToContinue();
			display("\n\"Are you doubting our boy's abilities, Trent?!\"\n");
			enterToContinue();
			display("\n\"I'm just saying you could do with a bit less of the ale, that's all...\"\n");
			enterToContinue();
			WorldVars.Elffor.NinaConversationHad = true;
		} else
			display("\"Why, I'm sure you could take down a wolf with your bare hands, lad!\"\n");
	}
}

FUNCACTION(ElfforTavernWaitUntilDay)
{
	if (WorldVars.IsDay == false) {
		display("Trent walks in and gasps when he sees you.  \"How did you get in here?!...  Well, whatever, you're harmless enough.  Just don't scare me like that again.\"\n");
		WorldVars.IsDay = true;
	} else
		display("But it already is day...\n");
}

FUNCACTION(ElfforTavernWaitUntilNight)
{
	if (WorldVars.IsDay == true) {
		display("You stay until closing, at which point Trent leads you to the door.  \"Sorry, friend, but you can't stay here for the night.\"\n");
		enterToContinue();
		cout << '\n';
		PC.setCurrentLocation(ELFFORTAVERN);
		WorldVars.IsDay = false;
	} else
		display("But it is already night...\n");
}

FUNCACTION(EnterElffor)
{
	PC.setCurrentLocation(ELFFORGATE);
	WorldVars.RoadToElffor.BattleFought = false;
}

FUNCACTION(RoadToElfforGoDownPath)
{
	if (WorldVars.RoadToElffor.BattleFought)
		display("This is where you'd move to a new area.\n"); // temp code
	else {
		if ((! WorldVars.IsDay) && (! PC.isInInventory(LANTERN))) {
			display("In the dark of the night, made only more impregnable by the thick woods, you could only hear the wolf moving through the brush.\
  By the time you saw him, he was already at your throat.\n");
			PC.killPlayer();
		} else if (! PC.isInInventory(RUSTYSWORD)) {
			display("A wolf leaps out from the brush and sprints towards you.  Alas, with no means of defending yourself, you become its next dinner.\n");
			PC.killPlayer();
		} else {
			display("A wolf leaps out from the brush, intent on making you its dinner.  Seeing the wolf coming at you, you slay the beast with your sword.\
  The path is now safe to walk.\n");
			WorldVars.RoadToElffor.BattleFought = true;
		}
	}
}