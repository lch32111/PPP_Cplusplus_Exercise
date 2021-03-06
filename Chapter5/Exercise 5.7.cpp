//Chapter 5.7
#include "std_lib_facilities"

double square(double x);
vector<double> quadratic_formula(double a, double b, double c);

int main()
try
{
	double a{ 0 };
	double b{ 0 };
	double c{ 0 };

	cin >> a >> b >> c;

	vector<double> solutions = quadratic_formula(a, b, c);

	cout << "The solutions are.. (" << solutions[0]
		<< ", " << solutions[1] << ")\n";
	
	return 0;
}
catch (exception& e)
{
	cerr << "error : " << e.what() << "\n";
	return 1;
}

vector<double> quadratic_formula(double a, double b, double c)
{
	vector<double> solutions(2);
	if ((square(b) - 4 * a * c) < 0) 
		error("There is no solution because the value is 0 in the root");

	solutions[0] = ((-1 * b) + sqrt(square(b) - 4 * a *c)) / (2 * a);
	solutions[1] = ((-1 * b) - sqrt(square(b) - 4 * a *c)) / (2 * a);

	return solutions;
}

double square(double x)
{
	return x * x;
}