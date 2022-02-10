#ifndef COMMAND_H
#define COMMAND_H

#include "base.h"


#include <iostream>
#include <string>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream> //for when your using .c_str()
#include <vector>
#include <unistd.h> //this is for the fork commands in the end
#include <cstdio>

#include <cstdlib>

using namespace std;


class Command : public Base{
  public:
    Command() {};
    
	


	bool construct() {
		struct stat set;
	  //command will exit if the word exit is put
		if (comm[0] == "exit") {  
			exit(EXIT_SUCCESS);
		}   //this is if any other term comes 
			else if (comm[0] == "test" || comm[0] == "[") {
			//	struct stat set;

				if (comm[1] == "-e") {
					string data  = comm[2];  //this is the path for the command that is being run in

					if (!stat(data.c_str(), &set)) {
						cout << "(True)\n";
						return true;
					}

					cout << "(False)\n";
					return false;
				}

                        // Detects true if the file is valid
				else if (comm[1] == "-f") {
					string data = comm[2];

					if (stat(data.c_str(), &set)) {
						cout << "(False)\n";
						return false;
					}
                                          //this is as instructed in the specs
					if (S_ISREG(set.st_mode)) {
						cout << "(True)\n";
						return true;
					}

				cout << "(False)\n";
				return false;
			}
			// Detects true if directory is valid

				else if (comm[1] == "-d") {
					string data = comm[2];

					if (stat(data.c_str(), &set)) {
						cout << "(False)\n";
						return false;
					}

					if (S_ISDIR(set.st_mode)) {
						cout << "(True)\n";
						return true;
					}

					cout << "(False)\n";
					return false;
				}

				return true;
			}

			vector<char *> points;
                 

//it changes your time to the one acceptable for the execvp call, if its not there you cant do th execvp call, 
//you get mismatching data types
			for (unsigned int g = 0; g < comm.size(); ++g) {
				points.push_back(const_cast<char *>(comm[g].c_str()));
			}

				points.push_back(nullptr);

				pid_t pid = fork(); // Forks new process

			if (pid > 0) {
				// Initialize variabbles for child process
				int childStatus;

				if (waitpid(pid, &childStatus, 0) == -1) {
					perror("wait");
				}

					if (WEXITSTATUS(childStatus) != 0) {
						return false;
				}	
			}
			// test cases of child
			else if (pid == 0) {
				//we now have to take care of the dup functionality
				//all command specific for dup     				
				int outputFile = dup(1); //stardard out, gets file description of 3, since its the lowest value
                                if(dup2(fileInput,  STDIN_FILENO) == -1) {  //speific documentation for input
					perror("we are using dup2");
					return false;
				}

				if(dup2(fileOutput,  STDOUT_FILENO) == -1) { //this is specific documentation for output 
					perror("we are using dup2");
					return false;
				}

				if (execvp(points[0], points.data()) == -1) {
					dup2(outputFile, STDOUT_FILENO); //by default we bring it here
					cout << "rshell " << points[0] << ":wasn't found in this command" << endl;
					exit(EXIT_FAILURE);
				}
			}
			else if (pid < 0) {
				perror("fork"); //is now being run in this terminal
				return false;
			}

			return true; //by default this will run tree 
	}
};
#endif
