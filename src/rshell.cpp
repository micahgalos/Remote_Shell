#include "rshell.h"

// Connectors
#include "and.h"
#include "or.h"
#include "semicolon.h"

// Redirection
#include "in.h"
#include "out.h"
#include "doubleout.h"
#include "piping.h"

using namespace std;

//temp is the for the recusive calls and connectList is between parenthesis when given a command
void RShell::connectParsing(unsigned int temp, vector<connectStrings*> & connectList) {    	
	connectStrings* connectors;
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
						connectors = new connectStrings(listUser[g]);
						connectList.push_back(connectors); 
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
						connectors = new connectStrings(listUser[g]);
						connectParsing(++temp, connectors ->templist);
						connectList.push_back(connectors);
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
						connectors = new connectStrings(listUser[g]);
						connectParsing(++temp, connectors->templist);
						connectList.push_back(connectors);
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
							connectors = new connectStrings(listUser[g]);
							connectList.push_back(connectors);
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
				connectors = new connectStrings(listUser[g]);
				connectList.push_back(connectors);
			}
		}
		g = temp;
	}    
}

Base* RShell::designtree(vector<connectStrings*> connectList) {
	Base* leftside; //left hand side of the command which is seperated by a connector
	Base* rightside; //right hand side of the command which is seperated by a connector
	Base* connects = 0; //this is the result that is formed from a tree and shown in the vector as a final result

	for (unsigned int g = 0; g < connectList.size(); ++g) { //this is the iteration through the command and it takes note of the connectors that it sees  
		if (connectList[g]->num == ";") {  //this is specific to the ; collector if it comes in a command
			if (treeDesign.empty()) {   //tree starts out being empty b/c nothing in it
				if (connectList[g]->templist.empty()) { //this case assumes that there is no parentheses within the command such as echo a; echo b  
					leftside = commandlist.front(); //this takes in the left hand size of the command and forms it into a tree
					commandlist.pop(); //this command actually forms the tree
					rightside = commandlist.front(); //this takes in the right hand size ofthe command and sets up it to be formed
					commandlist.pop(); //this actually forms the tree 
					connects = new Semicolon(leftside, rightside); //connector has all the commands to push back into the tree
					treeDesign.push_back(connects); //this pushes it back into a tree vector to show the final answer
				}

				else {
					leftside = commandlist.front(); //if there parenthesis that will always be on the right
					commandlist.pop();   //this forms the left hand side of the tree and actually does it
					rightside = designtree(connectList[g]->templist);  //assumes the parentheses are on the right 	
					connects = new Semicolon(leftside, rightside); // connector that has all the commands to push back into the tree
					treeDesign.push_back(connects); //puts the commands output into a tree vector to show the answer
				}
			}
		
			else {
				if (connectList[g]->templist.empty()) {     
					leftside = treeDesign.back(); //saying that there is something in the commandtree because you didnt clear like asked in the end  
					treeDesign.pop_back();  //you have to make hand side the back if the tree isnt cleared to start with 
					rightside = commandlist.front(); //this forms the command from the left hand side
					commandlist.pop(); //this takes in the right hand size of the command and sets up it to be formed
					connects = new Semicolon(leftside, rightside); //this forms the tree on the right hand side of it 
					treeDesign.push_back(connects); //connector that has all the commands to push back into the tree
				}
				else {
					leftside = treeDesign.back(); //assuming parthesis and there is something in the command tree     
					treeDesign.pop_back(); // this forms the command from the left hand side 
					rightside =designtree(connectList[g]->templist); //assumes the parentheses are on the right
					connects = new Semicolon(leftside, rightside); //connector that has all the commands to push back into the tree
					treeDesign.push_back(connects); //puts the commands output into a tree vector to show the answer
				}
			}
		}

		else if (connectList[g]->num == "&&") { //follows the same format as above but with and connector
			if (treeDesign.empty()) {
				if (connectList[g]->templist.empty()) {
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
					rightside = designtree(connectList[g]->templist);
					connects = new And(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectList[g]->templist.empty()) {
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
					rightside = designtree(connectList[g]->templist);
					connects = new And(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectList[g]->num == "||"){ //follows the same format as above but with or connector
			if (treeDesign.empty()) {
				if (connectList[g]->templist.empty()) {
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
					rightside = designtree(connectList[g]->templist);
					connects = new Or(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectList[g]->templist.empty()) {
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
					rightside = designtree(connectList[g]->templist);
					connects = new Or(leftside, rightside);
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectList[g]->num == "<"){ 
		// follows the same format as above but with input
		// redirection connector
			if (treeDesign.empty()) {
				if (connectList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new In(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectList[g]->templist);
					connects = new In(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new In(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectList[g]->templist);
					connects = new In(leftside, rightside, "<");
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectList[g]->num == ">"){ 
		//follows the same format as above but with output                                                
		//redirection connector
			if (treeDesign.empty()) {
				if (connectList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Out(leftside, rightside,">");
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectList[g]->templist);
					connects = new Out(leftside, rightside, ">");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new Out(leftside, rightside, ">");
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectList[g]->templist);
					connects = new Out(leftside, rightside, ">");
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectList[g]->num == ">>"){ 
		//follows the same format as above but with
		// double output redirection connector
			if (treeDesign.empty()) {
				if (connectList[g]->templist.empty()) {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new DoubleOut(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
				else {
					leftside = commandlist.front();
					commandlist.pop();
					rightside = designtree(connectList[g]->templist);
					connects = new DoubleOut(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectList[g]->templist.empty()) {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = commandlist.front();
					commandlist.pop();
					connects = new DoubleOut(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
				else {
					leftside = treeDesign.back();
					treeDesign.pop_back();
					rightside = designtree(connectList[g]->templist);
					connects = new DoubleOut(leftside, rightside, ">>");
					treeDesign.push_back(connects);
				}
			}
		}

		else if (connectList[g]->num == "|"){ //follows the same format as above but with pipe connector
			if (treeDesign.empty()) {
				if (connectList[g]->templist.empty()) {
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
					rightside = designtree(connectList[g]->templist);
					connects = new Piping(leftside, rightside, "|");
					treeDesign.push_back(connects);
				}
			}
			else {
				if (connectList[g]->templist.empty()) {
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
					rightside = designtree(connectList[g]->templist);
					connects = new Piping(leftside, rightside, "|");
					treeDesign.push_back(connects);
				}
			}
		}
	}

	treeDesign.clear(); //clears the tree everytime so you can see the new commands with connectors in the middle
	return connects; // the new connectors that are a result and the right hand side if there is parenthesis involved 
}