#ifndef TOKEN_H
#define TOKEN_H

#include "std_lib_facilities.h"

class Token {
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	string name;
	Token(char ch) :kind{ ch } {}  // initialize kind with ch
	Token(char ch, double val)     // make a Token from a char and a double
		:kind{ ch }, value{ val } { }
	Token(char ch, string n)
		:kind{ ch }, name{ n } {}
};

#endif