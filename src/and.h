#ifndef AND_H
#define AND_H

#include "connect.h"

class And : public Connect {
	public:
	And() { }

    And(Base* left, Base* right) {
		this->left = left;
		this->right = right;
	}
    
	// Construct command when conditions are true
    bool construct(){
		if(left->construct()) { return right->construct(); }
		return false;
	}
};
#endif
