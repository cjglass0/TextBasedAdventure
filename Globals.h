#ifndef GLOBALS_H
#define GLOBALS_H

// Putting all the libraries I use here so I don't have to worry about whether they were included in a previous file or not as I write the code.
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

typedef unsigned int uint;

#define OnOff(X) ((X) ? "On" : "Off") // Takes a bool and turns it into an "On" output or an "Off" output.  Used in menus.

enum Area {TOWNCENTER = 1, TOWNHALL, TOWNHALLLOBBY, THIEFSHOUSE, THIEFSHOUSEINTERIOR, AREAENDMARKER};
#define StartingLocation TOWNCENTER // Defines the area the game will start you in.

enum status {OK = 1, ERROR = 0};

#endif