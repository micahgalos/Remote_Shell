#ifndef CONNECT_H
#define CONNECT_H

#include "base.h"
#include <iostream>
using namespace std;

class Connect : public Base{

   protected:
    Base* left;
    Base* right;



   public:
    Connect() {
     left = 0;
     right = 0;
    };
    
    virtual bool construct() = 0;

};




#endif
