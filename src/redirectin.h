#ifndef REDIRECTIN_H
#define REDIRECTIN_H

#include "redirect.h"

#include <iostream>
#include <string>
#include <unistd.h> //this is the libarary for the fork command
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

//this is for this command <, I got the specific commands for it based off what the bash told me and videos I found online
class RedirectIn : public Redirect{
	public:
	RedirectIn() { }
	RedirectIn(Base* left, Base* right, string command) : Redirect(left,right,command) {  }

	bool construct() {
		string ots = right->receiveArg();
		int fileInput = open(ots.c_str(), O_RDONLY);  //specific for dup, getting the file descriptor 
		
		if(fileInput == -1) {
			cout << "error in the Rshell :in the ots" << ots << "its not there" ;
			cout << endl;
			return false;
		}

		left->fileInput = fileInput;
		left->fileOutput = fileOutput;
		return left->construct();
	}
};
#endif