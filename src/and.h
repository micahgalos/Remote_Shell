#ifndef AND_H
#define AND_H


#include "connect.h"
using namespace std;


class And : public Connect {

    public:
     And() { }

     And(Base* left, Base* right) {
        this->left = left;
        this->right = right;

     }
     //this connector will only execute the command if the first argument does then second one will follow it
     bool construct(){
     	if(left->construct()) {
		return right-> construct();
	}
	return false;
      }

};

#endif
