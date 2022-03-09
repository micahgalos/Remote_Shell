#ifndef CONNECT_H
#define CONNECT_H

#include "base.h"

class Connect : public Base{
    protected:
    Base* left;
    Base* right;

    public:

    // left [connect] right
    Connect() {
        left = 0;
        right = 0;
    };
    
    virtual bool construct() = 0;
};
#endif
