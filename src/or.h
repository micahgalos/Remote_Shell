#ifndef OR_H
#define OR_H

#include "connect.h"

class Or : public Connect {
	public:
	Or() { }
	Or(Base* left, Base* right) {
		this->left = left;
		this->right = right;
	}

    // Construct command when at most one is true
	bool construct() {
		if(!(left->construct() ) ) { return right->construct(); }  
        return true;
	}
};
#endif

