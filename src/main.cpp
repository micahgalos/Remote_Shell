#include "rshell.h"

using namespace std;

int main() {
    RShell terminal;		
    string command;
    while(command != "exit"){
        terminal.interface();
        getline(cin, command);
        if(command == "exit"){
            break;
        }
        terminal.parsing(command); //commands  in parse to help with main
        terminal.commandDesign(); //pops the commands out of the list and runs them for the function
    }
    return 0;
}