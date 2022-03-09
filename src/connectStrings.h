#ifndef __CONNECTSTRINGS_H__
#define __CONNECTSTRINGS_H__

#include "csheaders.h"

class connectStrings {
	public:
	connectStrings(const string & num) : num(num) { }
    vector<connectStrings*> templist; // cmds are contained in balance parenthesis
    string num; // determines connector
};
#endif