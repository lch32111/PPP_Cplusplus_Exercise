#include "Calculator.h"

Calculator::Calculator()
{
	// ROMAN INTEGER
	define_name("I", 1, false);
	define_name("V", 5, false);
	define_name("X", 10, false);
	define_name("L", 50, false);
	define_name("C", 100, false);
	define_name("D", 500, false);
	define_name("M", 1000, false);
}

double Calculator::define_name(string var, double val, bool convert)
// add (var,val) to symbol_table
{
	// Const declaration
	if (convert == false) symbol_table.push_back(Variable(var, val, convert));
	// Variable declaration
	else if (convert == true) symbol_table.push_back(Variable(var, val, convert));

	return val;
}

double Calculator::disable_convert(string var, double val)
// let normal variable be const variable
{
	for (Variable& v : symbol_table)
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


double Calculator::declare(Token_stream& ts)
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

double Calculator::constdeclare(Token_stream& ts)
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

bool Calculator::is_declared(string var)
{
	for (const Variable& v : symbol_table)
		if (v.name == var) return true;
	return false;
}

double Calculator::get(string s)
{
	for (const Variable& v : symbol_table)
		if (v.name == s) return v.value;
	error("get: undefined variable ", s);
}

void Calculator::set(string s, double d)
{
	for (Variable& v : symbol_table)
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

bool Calculator::is_convert(string s)
{
	for (const Variable& v : symbol_table)
		if (v.name == s) return v.Convert;

	return true; // the string s is not in var table -> thus, it can convert
}

double Calculator::statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declare(ts);
	case Uconst:
		return constdeclare(ts);
	default:
		ts.putback(t);
		return expression();
	}
}

void Calculator::calculate()
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

double Calculator::primary()
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
			set(t.name, d);
			return d;
		}
		else
		{
			ts.putback(t2);
			return get(t.name);
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
		if (is_declared(t.name))
			return get(t.name);
		error("primary expected");
	}

	return 0.0;
}

double Calculator::suffix()
{
	double left = primary();
	Token t = ts.get();

	while (true)
	{
		switch (t.kind)
		{
		case'!':
		{
			int left_int = (int)left;

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
double Calculator::term()
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
double Calculator::expression()
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

void Calculator::clean_up_mess()
{
	ts.ignore('\n');
}

//------------------------------------------------------------------------------

void Calculator::show_help()
{
	cout << "This is a calculator!\n"
		<< "You can calculate by pressing 'enter key' after giving the calculator expression\n"
		<< "You can declare variables. for example, 'let a = 3' or 'const a = 3'\n"
		<< "If you declare a variable by const, you can't change the value of the number.\n"
		<< "If not, you can change the value. e.g., a = 5\n"
		<< "You can use factorial and float modulo!\n"
		<< "You can use Roman integer, using the uppercase characters. "
		<< "To exix this program, enter the 'quit'\n";
}