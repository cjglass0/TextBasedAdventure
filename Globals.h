#ifndef GLOBALS_H
#define GLOBALS_H

// Putting all the libraries I use here so I don't have to worry about whether they were included in a previous file or not as I write the code.
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

typedef unsigned int uint;

#define OnOff(X) ((X) ? "On" : "Off") // Takes a bool and turns it into an "On" output or an "Off" output.  Used in menus.

enum Area {TOWNCENTER = 1, TOWNHALL, TOWNHALLLOBBY, THIEFSHOUSE, THIEFSHOUSEINTERIOR};
enum status {OK = 1, ERROR = 0};

#endif