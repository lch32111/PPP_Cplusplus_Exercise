#ifndef VARIABLE_H
#define VARIABLE_H

#include "std_lib_facilities.h"

class Variable
{
public:
	string name;
	double value;
	bool Convert;

	Variable(string var, double val)
		:name(var), value(val), Convert(false) { }
	Variable(string var, double val, bool convert)
		:name(var), value(val), Convert(convert) { }
};


#endif