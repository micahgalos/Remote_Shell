#ifndef SEMICOLON__H
#define SEMICOLON__H

#include "connect.h"

class Semicolon : public Connect {
    public:
    Semicolon() { }
    Semicolon(Base* left, Base* right) {
		this->left = left;
		this->right = right;
	}

	// Construct command when cmd follows another cmd
	bool construct() {
		left->construct();
		right->construct();
		return true;
    }

};
#endif

