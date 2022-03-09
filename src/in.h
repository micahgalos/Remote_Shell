#ifndef IN_H
#define IN_H

#include "redirect.h"

//this is for this command <, I got the specific commands for it based off what the bash told me and videos I found online
class In : public Redirect{
	public:
	In() { }
	In(Base* left, Base* right, string command) : Redirect(left,right,command) {  }

	bool construct() {
		string ots = right->receiveArg();
		int fileInput = open(ots.c_str(), O_RDONLY);  //specific for dup, getting the file descriptor 
		
		if(fileInput == -1) {
			cout << "error in the Rshell :in the ots" << ots << "its not there\n";
			return false;
		}

		left->fileInput = fileInput;
		left->fileOutput = fileOutput;
		return left->construct();
	}
};
#endif