#ifndef RSHELL_H__
#define RSHELL_H__

#include "base.h"
#include "connectingStrings.h"

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <stack>

using namespace std;

class rShell{ 
	public:
    rShell() {}; 
    void show();
    void clear();
    void parenthesisParsing();
    void commentParsing();
    void userSplitting();
    void userSpacing();
    void connectParsing(unsigned int temp, vector<connectingStrings*> & connectingList);
    void parsing(string commandline);
    void commandDesign();
    void constructCommands();
    Base * designtree(vector<connectingStrings*> connectingList);

	private:
    queue<Base*> commandlist;
    vector<Base*> treeDesign;
    vector<connectingStrings*> connectingList;
    vector<unsigned int> vecdex;
    stack<string> parenthesis;
    vector<string> listUser;
    string userInput;
    Base* cmd;
};
#endif