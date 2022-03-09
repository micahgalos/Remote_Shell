#ifndef RSHELL_H_
#define RSHELL_H_

#include "base.h"
#include "command.h"
#include "connectStrings.h"

class RShell{ 
	public:
    RShell() {};

    // first line on start-up
    void interface() { cout << "$ "; }

    // this is to clears all the vectors in the process of doing the parsing for 
    // the command and connectors that are  going through the command to give the answer
    void clear(){
        listUser.clear();
        vecdex.clear();
        connectList.clear();
        if (!parenthesis.empty()){	
            stack<string>().swap(parenthesis);
        }
    }

    // lets say see echo a;(echo b; echo c), we dont need parenthesis 
    // so this functions deletes those parenthesis
    void parenthesisParsing(){
        for (unsigned int g = 0; g < listUser.size(); ++g) {
            if (listUser[g] == "(" || listUser[g] == ")") {
                listUser.erase(listUser.begin() + g);
                --g;
            }
        }
    }

    // ignores commands that we may see that have a # in front 
    // because they are not necessary
    void commentParsing(){
        for (unsigned int g = 0; g < userInput.size(); ++g) {
            if (userInput[g] == '#') {
                userInput.erase(g, userInput.size() - 1);
                break;
            }
        }
    }

    // after the userSpacing, if there are two things in the command 
    // that are indexices then it makes sure that they are split 
    void userSplitting(){
        istringstream istream(userInput);
        string tokening;
        while(istream >> tokening) { listUser.push_back(tokening); }
    }

    // this is a function that takens in the spacing between the command 
    // for example if we had echo  a; separates each command argument into one index
    void userSpacing(){
        for (unsigned int g = 0; g < userInput.size(); ++g) {
            switch (userInput[g]) {
			    case ';':  //these are cases and I was looking at for the spacing 
                if (g > 0) { (userInput[g - 1] != ' ') ? userInput.insert(g, " ") : userInput; }
                (userInput[g + 1] != ' ') ? userInput.insert(g + 1, " ") : userInput;
                ++g;
                break;

			    case '(':  //another case where you focus on a parenthesis
                if (g > 0) { (userInput[g - 1] != ' ') ? userInput.insert(g, " ") : userInput; }
                (userInput[g + 1] != ' ') ? userInput.insert(g + 1, " ") : userInput;
                ++g;
                break;

                case ')':
                if (g > 0) { (userInput[g - 1] != ' ') ? userInput.insert(g, " ") : userInput; }
                (userInput[g + 1] != ' ') ? userInput.insert(g + 1, " ") : userInput;
                ++g;
                break;

			    default:     //when its not specifed this case automatically will break meaning end 
                break;
            }
        }
    }
    void connectParsing(unsigned int temp, vector<connectStrings*> & connectList);

    // ( to ) and more
    void parsing(string commandline){
        unsigned int temp = 0;
        userInput = commandline;
        clear();
        commentParsing();
        userSpacing();
        userSplitting();
        connectParsing(temp, connectList);
        parenthesisParsing();	
    }
    
    // checks for at least two commands with a connect so that we can 
    // build a tree to get the answer for the user command
    void commandDesign(){
        constructCommands();
        if (commandlist.size() >= 2) {
            treeDesign.push_back(designtree(connectList));
            while (!treeDesign.empty()){
                    treeDesign.back()->construct();
                    treeDesign.pop_back();
            }
        }
        else {
            while (!commandlist.empty()) {
                    commandlist.front()->construct();
                    commandlist.pop();
            }
        }
    }

    // this is simple case of echo a; echo b where you check 
    // for one command and you parse another accordingly
    // commandlist has all the commands due to the pushes 
    void constructCommands(){
	    cmd = new Command(); //this is an inializer 
        bool next = true;
        for (unsigned int g = 0; g < listUser.size(); ++g) {
            bool b1 = listUser[g] == ";" || listUser[g] == "||";
            bool b2 = listUser[g] == "&&" || listUser[g] == "<";
            bool b3 = listUser[g] == ">" || listUser[g] == ">>";
            bool b4 = b1 || b2;
            bool b5 = b3 || listUser[g] == "|";
            bool b6 = b4 || b5;
            if (b6){			
                commandlist.push(cmd);
	    		//we do it again for the second time
                if ((g + 1) < listUser.size()) { cmd = new Command(); }
                else { next = false; }
            }
	    	//still need to create this in base file 
            else { cmd->comm.push_back(listUser[g]); }
        }
        if (next) { commandlist.push(cmd); }
    }

    Base * designtree(vector<connectStrings*> connectList);

	private:
    queue<Base*> commandlist;
    vector<Base*> treeDesign;
    vector<connectStrings*> connectList;
    vector<unsigned int> vecdex;
    stack<string> parenthesis;
    vector<string> listUser;
    string userInput;
    Base* cmd;
};
#endif