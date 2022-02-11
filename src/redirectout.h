#ifndef REDIRECTOUT_H
#define REDIRECTOUT_H

#include "redirect.h"

#include <iostream>
#include <string>
#include <unistd.h> //this is the libarary for the fork command
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

//this is for the command >, I got the specific commands for it based off what the bash told me and videos I found online 
class RedirectOut : public Redirect{
	public:
    RedirectOut() { }
	RedirectOut(Base* left, Base* right, string command) : Redirect(left,right,command) {  }

    bool construct() {
		string ots = right->receiveArg();
		//getting the file descriptor
        int fileOutput = open(ots.c_str(),O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if(fileOutput == -1) {
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