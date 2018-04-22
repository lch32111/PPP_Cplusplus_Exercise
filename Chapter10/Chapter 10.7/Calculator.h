#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "std_lib_facilities.h"
#include "Token_stream.h"
#include "Variable.h"

/*
Simple Calculator

Revision history:

Revised by BS November 2013
Revised by BS May 2007
Revised by BS August 2006
Revised by BS August 2004
Originally written by BS
(bs@cs.tamu.edu) Spring 2004.
----------------------------
Revised by Chan March 28 2018
Revised by Chan March 30 2018 + added Roman integer system

This program implements a basic expression calculator.
input from cin; output to cout.
The grammar for input is:

** Expression:
Term
Expression + Term
Expression - Term

Term:
Suffix
Term * Suffix
Term / Suffix
Term % Suffix

Suffix:
Primary
! Primary (factorial)

Primary:
Number
( Expression )
{ Expression }
- Primary
+ Primary
sqrt (double)
pow (double, int)

Number:
floating-point-literal

Calculation:
1. Statement
2. Print
3. Quit
4. Help
5. Calculation Statement

1. Statement:
1) Declaration
** Expression

1) Declaration:
"let" Name "=" Expression
"const" Name "=" Expression

2. Print:
newline

3. Quit:
"quit"

4. Help:
"help"

You can modify the keyworkd for Print, Quit, Help in the Token_Stream hedaer file.
Input comes from cin thorugh the Token_stream called ts.

You can use Roman integer system, using the uppercase characters.

Class
Token_stream - Token : Token_stream and Token are used to take user inputs
Variable + vector<Variable> : Variable are used to save variables and retrieve the variables
*/

class Calculator
{
private:
	/* Symbol Table*/
	vector<Variable> symbol_table;
	double disable_convert(string var, double val);
	double declare(Token_stream& ts);
	double constdeclare(Token_stream& ts);
	bool is_declared(string var);
	bool is_convert(string var);
	double get(string s);
	void set(string s, double d);
	/* Symbol Table*/

	double statement();
	double primary();
	double suffix();
	double term();
	double expression();
	
	void clean_up_mess();
	void show_help();
	
	Token_stream ts;
public:
	Calculator();
	double define_name(string var, double val, bool convert);
	void calculate();
};

#endif