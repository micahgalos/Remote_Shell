#include <iostream> 

using namespace std;

#include "rshell.h"

int main() {
    rShell doit;		
    string command;
    while(command != "exit"){
        doit.show();
        getline(cin, command);
        if(command == "exit"){
            break;
        }
        doit.parsing(command); //commands  in parse to help with main
        doit.commandDesign(); //pops the commands out of the list and runs them for the function
    }
    return 0;
}