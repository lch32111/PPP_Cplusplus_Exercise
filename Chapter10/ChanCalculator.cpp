/*
Simple Calculator

Revision history:

Revised by BS November 2013
Revised by BS May 2007
Revised by BS August 2006
Revised by BS August 2004
Originally written by BS
(bs@cs.tamu.edu) Spring 2004.

This program implements a basic expression calculator.
input from cin; output to cout.
The grammar for input is:

Calculation:
Statement
Print
Quit
Help
Calculation Statement

Statement:
Declaration
Expression

Declaration:
"let" Name "=" Expression
"const" Name "=" Expression

Print:
newline

Quit:
"quit"

Help:
"help"

Expression:
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

Input comes from cin thorugh the Token_stream called ts.

Class
Token_stream - Token : Token_stream and Token are used to take user inputs
Symbol_table - Variable : Symbol_table and Variable are used to save variables and retrieve the variables

*/

#include "std_lib_facilities.h"
#include <cmath>

//------------------------------------------------------------------------------

const char number = '8';    // t.kind == number means that t is a number Token
const char quit = 'q';
const char print = '\n';
const string prompt = "> ";
const string result = "= ";    // used to indicate that what follows is a result
const char name = 'a';         // name token
const char let = 'L';          // declaration token
const char Usqrt = 'R';
const char Upow = 'P';
const char Uconst = 'C';
const char help = 'H';
const string declkey = "let";  // declaration keyword
const string sqrtkey = "sqrt";
const string powkey = "pow";
const string quitkey = "quit";
const string constantkey = "const";
const string helpkey = "help";

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

//------------------------------------------------------------------------------

class Token_stream 
{
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
	void ignore(char c);      // discard characters up to and including a c
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

class Symbol_table
{
private:
	vector<Variable> var_table;

public:
	double define_name(string var, double val, bool convert);
	double disable_convert(string var, double val);
	double declare();
	double constdeclare();
	bool is_declared(string var);
	bool is_convert(string var);

	double get(string s);
	void set(string s, double d);
};

//------------------------------------------------------------------------------

Token_stream ts;
double expression();    // declaration so that primary() can call expression()

						//------------------------------------------------------------------------------

						// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
	if (full)  // do we already have a Token ready?
	{      	  // remove token from buffer
		full = false;
		return buffer;
	}

	char ch;
	cin.get(ch);
	while (isspace(ch))
	{
		if (ch == '\n') return Token(print);
		cin.get(ch); // note that cin.get doesn't skip whitespcae
	}
	// cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch)
	{
	case '{':
	case '}':
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '!':
	case '=':
	case ',':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case'8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token(number, val);
	}
	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_') s += ch;
			cin.putback(ch);
			if (s == declkey) return Token(let);
			else if (s == sqrtkey) return Token(Usqrt);
			else if (s == powkey) return Token(Upow);
			else if (s == quitkey) return Token(quit);
			else if (s == constantkey) return Token(Uconst);
			else if (s == helpkey) return Token(help);
			return Token{ name,s };
		}
		error("Bad token!!\n");
	}
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
// c represents the kind of Token
{
	// first look in buffer:
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	// now search input;
	char ch = 0;
	while (cin.get(ch))
		if (ch == c) return;
}

//------------------------------------------------------------------------------

double Symbol_table::define_name(string var, double val, bool convert)
// add (var,val) to var_table
{
	// Const declaration
	if (convert == false) var_table.push_back(Variable(var, val, convert));
	// Variable declaration
	else if (convert == true) var_table.push_back(Variable(var, val, convert));

	return val;
}

double Symbol_table::disable_convert(string var, double val)
// let normal variable be const variable
{
	for (Variable& v : var_table)
	{
		if (v.name == var)
		{
			v.value = val;
			v.Convert = false;
			return val;
		}
	}

	error("There is no variable ", var);
}


double Symbol_table::declare()
// assume we have seen "let"
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
// declare convertible variable
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration or that name already declared");
	string var_name = t.name;

	// if The variable which user want to declare is already declared and not convertible
	if (!is_convert(var_name)) error(var_name, " can't be converted!");

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();

	if (is_declared(var_name))
		set(var_name, d);
	else
		define_name(var_name, d, true);

	return d;
}

double Symbol_table::constdeclare()
// assume we have seen "const"
// handle: name = expression
// declare a constant called "name" with the initial value "expression"
// declare a Constant
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in Constant declaration");
	string var_name = t.name;

	bool isDeclared = is_declared(var_name);
	bool isConvert = is_convert(var_name);

	// if The variable which user want to declare is already declared and not convertible
	if (isDeclared && !isConvert) error(var_name, " can't be converted!");

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in Const declaration of ", var_name);

	double d = expression();

	if (!isDeclared)
		define_name(var_name, d, false);
	else if (isDeclared && isConvert)
		disable_convert(var_name, d);


	return d;
}

bool Symbol_table::is_declared(string var)
{
	for (const Variable& v : var_table)
		if (v.name == var) return true;
	return false;
}

double Symbol_table::get(string s)
{
	for (const Variable& v : var_table)
		if (v.name == s) return v.value;
	error("get: undefined variable ", s);
}

void Symbol_table::set(string s, double d)
{
	for (Variable& v : var_table)
		if (v.name == s)
		{
			if (v.Convert == true)
			{
				v.value = d;
				return;
			}
			else
				error(s, " can't be convertible");
		}

	error("set: undefined variable", s);
}

bool Symbol_table::is_convert(string s)
{
	for (const Variable& v : var_table)
		if (v.name == s) return v.Convert;

	return true; // the string s is not in var table -> thus, it can convert
}

//------------------------------------------------------------------------------

// Token_stream ts;        // provides get() and putback() 

Symbol_table table;  //------------------------------------------------------------------------------


					 //------------------------------------------------------------------------------

					 // deal with numbers and parentheses
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '{':    // handle '{' expression '}'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}') error("'}' expected");
		return d;
	}
	case number:
		return t.value;  // return the number's value
	case name:
	{
		Token t2 = ts.get();
		if (t2.kind == '=')
		{
			double d = expression();
			table.set(t.name, d);
			return d;
		}
		else
		{
			ts.putback(t2);
			return table.get(t.name);
		}
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case Usqrt:   // sqrt ( expression )
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");

		double d = expression();

		t = ts.get();
		if (t.kind != ')') error("')' expected");

		if (d < 0) error("sqrt can be used with negative number");
		else    return sqrt(d);
	}
	case Upow:  // pow(x, i) -> expressions
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");

		double x = expression();

		t = ts.get();
		if (t.kind != ',') error("',' expected");

		int i = (int)expression();

		t = ts.get();
		if (t.kind != ')') error("')' expected");

		return pow(x, i);

	}
	default:
		// In case of user defined variables
		if (table.is_declared(t.name))
			return table.get(t.name);
		error("primary expected");
	}
}

double suffix()
{
	double left = primary();
	Token t = ts.get();

	while (true)
	{
		switch (t.kind)
		{
		case'!':
		{
			int left_int = left;

			if (left_int == 0) return 1;
			else if (left_int > 0)
			{
				for (int i = left_int; i >= 2; --i)     // factorial
					left_int *= (i - 1);

				return (double)left_int;
			}
			else
			{
				error("factorial generates errors!\n");
			}
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
	double left = suffix();
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= suffix();
			t = ts.get();
			break;
		case '/':
		{
			double d = suffix();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);     // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();      // read and evaluate a Term
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
	ts.ignore('\n');
}

//------------------------------------------------------------------------------

void show_help()
{
	cout << "This is a calculator!\n"
		<< "You can calculate by pressing 'enter key' after giving the calculator expression\n"
		<< "You can declare variables. for example, 'let a = 3' or 'const a = 3'\n"
		<< "If you declare a variable by const, you can't change the value of the number.\n"
		<< "If not, you can change the value. e.g., a = 5\n"
		<< "You can use factorial and float modulo!\n"
		<< "To exix this program, enter the 'quit'\n";
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return table.declare();
	case Uconst:
		return table.constdeclare();
	default:
		ts.putback(t);
		return expression();
	}
}



void calculate()
{
	while (cin)
	{
		try
		{
			cout << prompt;
			Token t = ts.get();

			while (t.kind == print) t = ts.get();     // eat ';'
			if (t.kind == quit) return;
			else if (t.kind == help)
			{
				show_help();
				cout << prompt;
				t = ts.get();
			}
			else
				ts.putback(t);

			cout << result << statement() << '\n';
		}
		catch (exception& e)
		{
			cerr << e.what() << '\n';
			clean_up_mess();
		}
	}


}

int main()
try
{
	// predefine names:
	table.define_name("pi", 3.1415926535, false);
	table.define_name("e", 2.7182818284, false);
	table.define_name("k", 1000, true);

	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

//------------------------------------------------------------------------------
