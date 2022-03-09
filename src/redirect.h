#ifndef REDIRECT_H
#define REDIRECT_H

#include "base.h"

class Redirect: public Base{
	protected:
	Base* left;
	Base* right;
	
	public:
	Redirect() { }
	Redirect(Base* left, Base* right, string command) : Base(command), left(left), right(right) { }
    //	this->left = left;
	//	this->right = right;
	//	commaand->this = command;

    virtual bool construct() = 0;
};
#endif 
