/*
10. Write a function vector<string> split(const string& s) 
that returns a vector of whitespce-separated substrings from the argument s.
*/

#include "std_lib_facilities.h"

vector<string> split(const string& s)
{
	vector<string> result;

	stringstream ss(s);

	string temp;
	while (ss >> temp)
		result.push_back(temp);

	return result;
}

int main()
{
	vector<string> v;
	string temp;
	getline(cin, temp);
	v = split(temp);

	for (string x : v)
		cout << x << '\n';
}