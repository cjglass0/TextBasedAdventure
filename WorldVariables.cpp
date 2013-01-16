#include "WorldVariables.h"

WorldVariables::WorldVariables()
{
	IsDay = true;
	
	Elffor.SwordRetrieved = false;
	Elffor.NinaConversationHad = false;
	
	RoadToElffor.BattleFought = false;
}

string WorldVariables::saveData()
{
	stringstream output;
	output << IsDay << ' ' << Elffor.SwordRetrieved << ' ' << Elffor.NinaConversationHad << ' ' << RoadToElffor.BattleFought << '\n' << ENDMARKER << '\n';
	return output.str();
}

void WorldVariables::loadData(string input)
{
	stringstream strstr(input);
	strstr >> IsDay >> Elffor.SwordRetrieved >> Elffor.NinaConversationHad >> RoadToElffor.BattleFought;
	
	strstr.ignore(1);
	LOADDATACHECK("WorldVariables")
}