#ifndef REDIRECT_H
#define REDIRECT_H

#include <iostream>
#include "base.h"
#include <string>
#include <unistd.h> //this is the libarary for the fork command
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;




class Redirect: public Base {

protected:

	Base* left;
	Base* right; 

public: 

	Redirect(Base* left, Base* right, string command) : Base(command), left(left), right(right) { }
        //	this -> left = left;
	//	this -> right = right;
	//	commaand -> this = command;

        virtual bool construct() = 0;

};
//this is for this command <, I got the specific commands for it based off what the bash told me and videos I found online
class Input_redirect : public Redirect {
   public:

	Input_redirect(Base* left, Base* right, string command) : Redirect(left,right,command) {  }

	bool construct() {
		string ots = right -> receiveArg();
		int fileInput = open(ots.c_str(), O_RDONLY);  //specific for dup, getting the file descriptor 
		
		if(fileInput == -1) {
			cout << "error in the Rshell :in the ots" << ots << "its not there" ;
			cout << endl;
			return false;

		}
		left -> fileInput = fileInput;
		left -> fileOutput = fileOutput;

	return left -> construct();
	}

};

//this is for the command >, I got the specific commands for it based off what the bash told me and videos I found online 
class Output_redirect : public Redirect {
   public:

        Output_redirect(Base* left, Base* right, string command) : Redirect(left,right,command) {  }

        bool construct() {
                string ots = right -> receiveArg();
		//getting the file descriptor
                int fileOutput = open(ots.c_str(),O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

                if(fileOutput == -1) {
                        cout << "error in the Rshell :in the ots" << ots << "its not there" ;
                        cout << endl;
                        return false;

                }
                left -> fileInput = fileInput;
                left -> fileOutput = fileOutput;

        return left -> construct();
        }



};

//this is for the comand >>, I got the specific commands for it based off what the bash told me and videos I found online
class DoubleOutput_redirect : public Redirect {
   public:
	
        DoubleOutput_redirect(Base* left, Base* right, string command) : Redirect(left,right,command) { }

        bool construct() {
                string ots = right -> receiveArg();
		//getting file descriptor
                int fileOutput = open(ots.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

                if(fileOutput == -1) {
                        cout << "error in the Rshell :in the ots" << ots << "its not there" ;
                        cout << endl;
                        return false;

                }
                left -> fileInput = fileInput;
                left -> fileOutput = fileOutput;

        return left -> construct();
        }





};

// this is for this command |, I got the specific commands for it based off what the bash told me and videos I found online
// one for reading and one for writing
class Piping : public Redirect {
   public:

        Piping(Base* left, Base* right, string command) : Redirect(left,right,command) { }

        bool construct() {
		if(fileOutput != 1) { //this is testing what you have italized 
			int file[2]; //returns two file descriptors to refer to two ends of the pipe
		
			if(pipe(file) == -1) {  //next we have to call pipe
				perror("piping at the moment");
				return false;
			}
                        left -> fileOutput = file[1]; //this is write end of the pipe
			if(!left -> construct()) {
				return false;
			}
			close(file[1]);  //closing file descriptor we want to replace
			
			right ->fileInput = file[0]; // this is the read end of the pipe
			right ->fileOutput = fileOutput;
				if(!right ->  construct()) {
					return false;
				}
			close(file[0]);  //closing the file desciptor we want to replace
			
			return true;

		}
                 //repeating process for other commands as well
		if(left -> command == "<") {
 			int file[2];

                        if(pipe(file) == -1) {
                                perror("piping at the moment");
                                return false;
                        }
                        left -> fileOutput = file[1];
                        if(!left -> construct()) {
                                return false;
                        }
                        close(file[1]);

                        right ->fileInput = file[0];
                     //   right ->fileOutput = fileOutput;
                                if(!right ->  construct()) {
                                        return false;
                                }
                        close(file[0]);

                 //       return true;
	


	      	}

	      	else {  //this happens with the default case still very similar tho

			int file[2];

                        if(pipe(file) == -1) {
                                perror("piping at the moment");
                                return false;
                        }
                        left -> fileOutput = file[1];
                        if(!left -> construct()) {
                                return false;
                        }
                        close(file[1]);

                        right ->fileInput = file[0];
                       // right ->fileOutput = fileOutput;
                                if(!right ->  construct()) {
                                        return false;
                                }
                        close(file[0]);

  
		

       		}
		return true;
	}
};

#endif 
