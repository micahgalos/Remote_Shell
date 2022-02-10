#ifndef OR_H
#define OR_H

#include <iostream>
#include "connect.h"
using namespace std;


class Or : public Connect {

    public:
     Or() { }
	
     Or(Base* left, Base* right) {
        this->left = left;
        this->right = right;

     }

      // the or connector will only execute if left hand argument fails then the right one will construct to excute
      bool construct() {
       	if(!(left -> construct() ) ) {
           return right -> construct();
        }  
        return true;
      }






};

#endif

