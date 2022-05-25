# CS 100 RShell Project

## Spring Quarter 2019
> Authors: George Awad, Micah Galos

## Introduction
We are creating an R-shell terminal for CS100 in the Spring 2019. We are bascially creating and running a Linux command shell that runs command prompts, reads lines of commands and connectors from standard inputs. We also are going to make sure that the connectors are seperated by either an OR, AND, or semicolon. Also, this will be constructed using a composite pattern approach to create a hierarchy of objects using our classes composite functionality.  

## UML Diagram
![UML Diagram](https://github.com/micahgalos/CS100_RShell_SPR19/blob/main/images/Assignment%20hw4.png?raw=true)

## Unit and Integration Tests
- The current build has the following bash integration test scripts:
  - commented_command_tests.sh
  - exit_command_tests.sh
  - multiple_command_tests.sh
  - single_command_tests.sh
  - precedence_tests.sh
  - test_literal_tests.sh
  - test_symbolic_tests.sh
  - input_redirection_tests.sh
  - output_redirection_tests.sh
  - pipe_operator_tests.sh
- The user can access these tests by the following:
```c++
cd CS100_RShell_SPR19/ -> cd integration_tests/ -> ./[bash script filename].sh 
```

## Classes
Base Class: rShell(named based off instructions)- this abstract base class will do the following
* void show - it displays the starting S in the command line
* void clear - clears all the vectors in the process of doing the parsing for the command and connectors
* void parenthesisParsing() - removes the parentheses in the command lineuserSplitting()
* void commentParsing() - ignores commands that we may see that have a # in front of them 
* void userSplitting() - if there are two things in the command that are indexices then it makes sure that they are split
* void userSpacing() - this is a function that takens in the spacing between the command for example if we had echo  a; seperates each command argument into one index
* void connectParsing() - temp is the for the recusive calls and connectingList is between parenthesis when given a command
* void parsing() - helps our exection in the main file so that we can know the process of the parser
* void constructCommands() -this is simple case of echo a; echo b where you check for one command and you parse another accordingly
* void commandDesign() - checks for at least two commands with a connect so that we can build a tree to get the answer for the user command
* Base designtree(vector<connectingStrings*> connectingList) - the designing of the tree to actually produce the answer

Base Class: Base- this is said to be the part where we allow the derived classes can their functions
* virtual Bool construct() = 0; - will be part of the that excutes that part of the function
* vector<string> comm - a public member function that is used in the constructCommand() in rshell

Dervied Class: Command- this is the storage of the parsing from the parse that the user inputs
* bool construct();- same as the base class and we had to add the child part of this class that has an exit option that will close the terminal when the user ends and the test command flags -e, -f (valid file), and -d (valid directory), default to -e if none are inputted by the user
* constructor as well due to using other functions
* we had to combine them all due to issues not getting the right command ouputs in the end.

Dervied class: Connector
* Virtual bool Construct() = 0 - which is a pure virutal and it allows us to use this fuction in our classes to excute their functionality
* Virtual bool Connect() = 0 - same as the base classes

* There is a class option for the OR, AND and semicolon to excute the functionalility for when it is called in the Rshell file. The classes are all derived classes and the and, or and semi_colon classes use the command of construct and they now have a constructor that is called in the rshell

Dervied class: Redirect
* Virtual bool Construct() = 0 - similar to connector, it allows the functions that it inherits to excute their functionality

* There is a class option for the functions for Indirect Redirection, Ouput Redirection, Double Redirection, and Pipe to excute the functionality for whne the rshell calls these files in the command desisgn function and this class option in the construct performs that action for us for the construct is also called in the rshell parsing to do any of the command the user desires

## Prototypes/Research 
We will require syscalls: fork(), execvp(), and wait()/waitpid() in order to simulate a terminal. Together these syscalls will make it possible for us to create shell commands, that a user will be able to use.

fork()
* The fork command creates a new process known as a child process which will run together with the parent process. The child process is technically a clone of the parent process as it uses the same program counter, registers, and open files. This command returns the process ID, or a negative value if the child process was failed. It also returns a zero to the child if created successfully.

execvp()
* Creats a child process just like the fork() syscall, but the child process doesn't have to run the same program as the parent process. Execvp() is passed in two arguments, the first one being a pointer to the program to be executed by the child process while the second argument is passed into said program. Has similar return values to those of fork()

wait()/waitpid()
* These commands will block the caller if any child or any specified child process is running when wait()/waitpid() calls are made, and will resume execution to caller after returning. wait() returns when any child exits, while waitpid() will return when the specified child exits.

## Development and Testing Roadmap
1. We did some research to draft up this plan but we need to do more to get a good idea of the main concpets for this lab
2. Next, we are going to review the 3 terms: waitpid(), execvp() and fork() functions once more to get the goals done for the next assignment and the future assignments
3. Our first coding task specifcally will be setting up the header and .cpp files for the base class and derived classes
4. We then will plan on adding extra functions if necessary to complete the functionality of this goal for the assignment 
5. Consistenly throught this part of the assignment and future ones we will be doing research to try to grasp the dieas of the function's purpose and task's purpose
6. We do this to be able to understand how to piece the shell together before we assign each other goals to accomplish for this command shell
7. Looking into the next parts of the assignment when they are assigned will help us postion set goals to finish assignments and be able to ease into the next one
8. Getting the big overall picture will help us in the long run when designing tasks to complete will help us set goals to maintain this project efficiently
9. We will be using the composite design pattern process as instructed in the assignments specs
10. To split the work, we collectively together want to create a working state to acheive command functionality
11. Finally, we will create the connectors and the important parsing for this assignment
