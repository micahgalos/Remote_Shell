#ifndef __CONNECTINGSTRINGS_H__
#define __CONNECTINGSTRINGS_H__

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <stack>

using namespace std;

class connectingStrings { //was made to check the connectors that are next to the parenthesis recursively
	public:
	connectingStrings(const string & num) :num(num) { }
    vector<connectingStrings*> templist; //everything thats within the parenthesis for commands and connectors
    string num; //the certain type of connector which is &&, ;, ||, <, >, >>, |
};
#endif