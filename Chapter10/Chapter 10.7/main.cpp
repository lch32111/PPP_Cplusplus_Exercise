#include "std_lib_facilities.h"
#include "Calculator.h"

int main()
try
{
	// predefine names:
	Calculator test;
	test.define_name("pi", 3.1415926535, false);
	test.define_name("e", 2.7182818284, false);
	test.define_name("k", 1000, true);
	test.calculate();
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
