/*
15. Write a program that reads a file of whitespace-separated numbers
and outputs a file of numbers using scientific format and precision 8 
in four fields of 20 characters per line.
*/

#include "std_lib_facilities.h"

int main()
{
	cout << "Enter the input file name : ";
	string iname;
	cin >> iname;
	ifstream ifs{ iname };

	if (!ifs) error("can't open input file ", iname);

	cout << "Enter the input file name : ";
	string oname;
	cin >> oname;
	ofstream ofs{ oname };

	if (!ofs) error("can't open output file ", oname);
	ofs <<  setprecision(8) << scientific;
	double x;
	while (ifs >> x)
	{
		ofs << setw(20) << x << '\n';
	}


	ifs.close();
	ofs.close();

	return 0;
}