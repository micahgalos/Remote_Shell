#ifndef __RSHELL_H__
#define __RSHELL_H__


#include "base.h"
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
