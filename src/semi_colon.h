#ifndef SEMI_COLON__H
#define SEMI_COLON__H

#include <iostream>
#include "connect.h"
using namespace std;


class Semi_colon : public Connect {

    public:
     Semi_colon() { }

     Semi_colon(Base* left, Base* right) {
	this->left = left;
	this->right = right;

     }

//semi_colon will also excute the command if the connector is used
     bool construct() {  
        left -> construct();
        right -> construct();

        return true;
     }




};

#endif

