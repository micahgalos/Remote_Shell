#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sstream>

#include "rshell.h"
#include "or.h" 
#include "semi_colon.h"
#include "and.h"
#include "connect.h"
#include "command.h"
#include "base.h"
#include "redirect.h" //added for part 4 of this assignment

using namespace std;

//starting screen of the command, the first line
void rShell::show() { cout << "$ "; }

//this is to clears all the vectors in the process of doing the parsing for the command and connectors that are  going through the command to give the answer
void rShell::clear() { 
    listUser.clear();
    vecdex.clear();
    connectingList.clear();
        if (!parenthesis.empty()){	
        stack<string>().swap(parenthesis);
    }
} 
//lets say see echo a;(echo b; echo c), we dont need parenthesis so this functions deletes those parenthesis
void rShell::parenthesisParsing() { 
    for (unsigned int g = 0; g < listUser.size(); ++g) {
        if (listUser[g] == "(" || listUser[g] == ")") {
            listUser.erase(listUser.begin() + g);
            --g;
        }
    }
}

//ignores commands that we may see that have a # in front of them because they are not necessary
void rShell::commentParsing() {
    for (unsigned int g = 0; g < userInput.size(); ++g) {
        if (userInput[g] == '#') {
            userInput.erase(g, userInput.size() - 1);
            break;
        }
    }
}
//after the userSpacing, if there are two things in the command that are indexices then it makes sure that they are split 
void rShell::userSplitting() {
    istringstream istream(userInput);
    string tokening;
    while(istream >> tokening) { listUser.push_back(tokening); }
}
//this is a function that takens in the spacing between the command for example if we had echo  a; seperates each command argument into     one index
//this had similarities to the C langauage it made the most sense to me, after thinking about it for awhile
// it goes back to when I used it in Embedded Systems
void rShell::userSpacing() {  	
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
//temp is the for the recusive calls and connectingList is between parenthesis when given a command
void rShell::connectParsing(unsigned int temp, vector<connectingStrings*> & connectingList) {    	
	connectingStrings* connectors;
	for (unsigned int g = temp; g < listUser.size(); ++g) {
		temp = g;
		
		if ((g + 1) < listUser.size()) {
			if (!parenthesis.empty()) { //first we find parenthesis
				if (listUser[g] == ")") {
					// lets stack know paren process is done and pop
					if (!parenthesis.empty()) { parenthesis.pop(); }
					vecdex.push_back(g);
					break;
				}
				
				// accounting for parenthesis in different locations
				if (listUser[g + 1] != "(") { 
					bool b1 = listUser[g] == ";" || listUser[g] == "&&";
					bool b2 = listUser[g] == ";" || listUser[g] == "&&";
					bool b3 = listUser[g] == ">" || listUser[g] == ">>";
					bool b4 = b1 || b2;
					bool b5 = b3 || listUser[g] == "|";
					bool b6 = b4 || b5;
					if (b6 ) {
						connectors = new connectingStrings(listUser[g]);
						connectingList.push_back(connectors); 
						//saved what you pushed in the commandline so you dont have to reset it
					}
				}

				else if (listUser[g + 1] == "(") {
					bool b1 = listUser[g] == ";" || listUser[g] == "&&";
					bool b2 = listUser[g] == "||" || listUser[g] == "<";
					bool b3 = listUser[g] == ">" || listUser[g] == ">>";
					bool b4 = b1 || b2;
					bool b5 = b3 || listUser[g] == "|";
					bool b6 = b4 || b5;
					if (b6) {
						parenthesis.push("(");
						connectors = new connectingStrings(listUser[g]);
						connectParsing(++temp, connectors ->templist);
						connectingList.push_back(connectors);
						temp = vecdex.back();
					}
				}
			}	
			
			else {
				if (listUser[g + 1] == "(") {
					bool b1 = listUser[g] == ";" || listUser[g] == "&&";
					bool b2 = listUser[g] == "||" || listUser[g] == "<";
					bool b3 = listUser[g] == ">" || listUser[g] == ">>";
					bool b4 = b1 || b2;
					bool b5 = b3 || listUser[g] == "|";
					bool b6 = b4 || b5;
					if (b6) {
						parenthesis.push("(");
						connectors = new connectingStrings(listUser[g]);
						connectParsing(++temp, connectors->templist);
						connectingList.push_back(connectors);
						temp = vecdex.back();
					}
				}
					else if (listUser[g + 1] != "(") {
						bool b1 = listUser[g] == ";" || listUser[g] == "&&";
						bool b2 = listUser[g] == "||" || listUser[g] == "<";
						bool b3 = listUser[g] == ">" || listUser[g] == ">>";
						bool b4 = b1 || b2;
						bool b5 = b3 || listUser[g] == "|";
						bool b6 = b4 || b5;
						if (b6) {
							connectors = new connectingStrings(listUser[g]);
							connectingList.push_back(connectors);
						}
					}
			}
		}
		
		else {
			if (listUser[g] == ")") {
				if (!parenthesis.empty()) { parenthesis.pop(); }
				vecdex.push_back(g);
				break;
			}
			bool b1 = listUser[g] == ";" || listUser[g] == "&&";
			bool b2 = listUser[g] == "||" || listUser[g] == "<";
			bool b3 = listUser[g] == ">" || listUser[g] == ">>";
			bool b4 = b1 || b2;
			bool b5 = b3 || listUser[g] == "|";
			bool b6 = b4 || b5;
			if (b6) {
				connectors = new connectingStrings(listUser[g]);
				connectingList.push_back(connectors);
			}
		}
		g = temp;
	}    
}

// ( to ) including multiple ones
void rShell::parsing(string commandline) {
    unsigned int temp = 0;
    userInput = commandline;
    clear();
    commentParsing();
    userSpacing();
    userSplitting();
    connectParsing(temp, connectingList);
    parenthesisParsing();	
}

//this is simple case of echo a; echo b where you check for one command and you parse another accordingly
//commandlist has all the commands due to the pushes  	
void rShell::constructCommands() {
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

//checks for at least two commands with a connect so that we can build a tree to get the answer for the user command
void rShell::commandDesign() {
	constructCommands();
	if (commandlist.size() >= 2) {
        treeDesign.push_back(designtree(connectingList));
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

Base* rShell::designtree(vector<connectingStrings*> connectingList) {
	Base* leftside; //left hand side of the command which is seperated by a connector
	Base* rightside; //right hand side of the command which is seperated by a connector
	Base* connects = 0; //this is the result that is formed from a tree and shown in the vector as a final result
    
	for (unsigned int g = 0; g < connectingList.size(); ++g) { //this is the iteration through the command and it takes note of the connectors that it sees  
    	if (connectingList[g]->num == ";") {  //this is specific to the ; collector if it comes in a command
			if (treeDesign.empty()) {   //tree starts out being empty b/c nothing in it
				if (connectingList[g]->templist.empty()) { //this case assumes that there is no parentheses within the command such as echo a; echo b  
					leftside = commandlist.front(); //this takes in the left hand size of the command and forms it into a tree
					commandlist.pop(); //this command actually forms the tree
					rightside = commandlist.front(); //this takes in the right hand size ofthe command and sets up it to be formed
					commandlist.pop(); //this actually forms the tree 
					connects = new Semi_colon(leftside, rightside); //connector has all the commands to push back into the tree
					treeDesign.push_back(connects); //this pushes it back into a tree vector to show the final answer
				}

				else {
					leftside = commandlist.front(); //if there parenthesis that will always be on the right
					commandlist.pop();   //this forms the left hand side of the tree and actually does it
					rightside = designtree(connectingList[g]->templist);  //assumes the parentheses are on the right 	
					connects = new Semi_colon(leftside, rightside); // connector that has all the commands to push back into the tree
					treeDesign.push_back(connects); //puts the commands output into a tree vector to show the answer
				}
			}
		
			else {
				if (connectingList[g]->templist.empty()) {     
					leftside = treeDesign.back(); //saying that there is something in the commandtree because you didnt clear like asked in the end  
					treeDesign.pop_back();  //you have to make hand side the back if the tree isnt cleared to start with 
					rightside = commandlist.front(); //this forms the command from the left hand side
					commandlist.pop(); //this takes in the right hand size of the command and sets up it to be formed
					connects = new Semi_colon(leftside, rightside); //this forms the tree on the right hand side of it 
					treeDesign.push_back(connects); //connector that has all the commands to push back into the tree
				}
				else {
					leftside = treeDesign.back(); //assuming parthesis and there is something in the command tree     
					treeDesign.pop_back(); // this forms the command from the left hand side 
					rightside =designtree(connectingList[g]->templist); //assumes the parentheses are on the right
					connects = new Semi_colon(leftside, rightside); //connector that has all the commands to push back into the tree
					treeDesign.push_back(connects); //puts the commands output into a tree vector to show the answer
				}
			}
		}

		else if (connectingList[g]->num == "&&") { //follows the same format as above but with and connector
			if (treeDesign.empty()) {
				if (connectingList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new And(leftside, rightside);
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectingList[g]->templist);
					connects = new And(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectingList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new And(leftside, rightside);
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectingList[g]->templist);
					connects = new And(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectingList[g]->num == "||"){ //follows the same format as above but with or connector
			if (treeDesign.empty()) {
				if (connectingList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Or(leftside, rightside);
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectingList[g]->templist);
					connects = new Or(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectingList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Or(leftside, rightside);
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectingList[g]->templist);
					connects = new Or(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectingList[g]->num == "<"){ //follows the same format as above but with input                                                 //redirection connector
			if (treeDesign.empty()) {
				if (connectingList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Input_redirect(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectingList[g]->templist);
					connects = new Input_redirect(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectingList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Input_redirect(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectingList[g]->templist);
					connects = new Input_redirect(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
			}
		}

	    else if (connectingList[g]->num == ">"){ //follows the same format as above but with output                                                //redirection connector
			if (treeDesign.empty()) {
				if (connectingList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Output_redirect(leftside, rightside,">");
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectingList[g]->templist);
					connects = new Output_redirect(leftside, rightside, ">");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectingList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Output_redirect(leftside, rightside, ">");
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectingList[g]->templist);
					connects = new Output_redirect(leftside, rightside, ">");
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectingList[g]->num == ">>"){ //follows the same format as above but with                                                      // double output redirection connector
			if (treeDesign.empty()) {
				if (connectingList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new DoubleOutput_redirect(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectingList[g]->templist);
					connects = new DoubleOutput_redirect(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectingList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new DoubleOutput_redirect(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectingList[g]->templist);
					connects = new DoubleOutput_redirect(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectingList[g]->num == "|"){ //follows the same format as above but with pipe connector
			if (treeDesign.empty()) {
				if (connectingList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Piping(leftside, rightside, "|");
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectingList[g]->templist);
					connects = new Piping(leftside, rightside, "|");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectingList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Piping(leftside, rightside, "|");
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectingList[g]->templist);
					connects = new Piping(leftside, rightside, "|");
					treeDesign.push_back(connects);
				}
			}
		}
	}

	treeDesign.clear(); //clears the tree everytime so you can see the new commands with connectors in the middle
	return connects; // the new connectors that are a result and the right hand side if there is parenthesis involved 
}