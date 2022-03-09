#ifndef DOUBLEOUT_H
#define DOUBLEOUT_H

#include "redirect.h"

//this is for the comand >>, I got the specific commands for it based off what the bash told me and videos I found online
class DoubleOut : public Redirect{
	public:
	DoubleOut() { }
    DoubleOut(Base* left, Base* right, string command) : Redirect(left,right,command) { }

    bool construct() {
		string ots = right->receiveArg();
		//getting file descriptor
        int fileOutput = open(ots.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if(fileOutput == -1) {
			cout << "error in the Rshell : in the ots " << ots << " does not exist\n";
			return false;
        }
		left->fileInput = fileInput;
		left->fileOutput = fileOutput;
		return left->construct();
    }
};
#endif