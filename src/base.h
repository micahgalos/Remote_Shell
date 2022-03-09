#ifndef BASE_H
#define BASE_H

#include "csheaders.h"

class Base {
	public:
	Base() {
		command = "";
		fileInput = 0;
		fileOutput = 1;
	}

	Base(string command) {
		this->command = command;
		fileInput = 0;
		fileOutput = 1;
	}

	const string receiveArg() const { return comm[0]; }

	virtual bool construct() = 0;
	vector<string> comm;
	string command;    
	int fileInput;
	int fileOutput;

	private:
};
#endif
