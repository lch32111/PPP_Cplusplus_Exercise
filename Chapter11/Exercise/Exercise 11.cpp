/*
11. Write a function vector<string> split(const string& s, const string& w) 
that returns a vector of whitespace-separeted substrings from the argument s, 
where whitespace is defined as "ordinary whitespace" plus the characters in w.
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

vector<string> split(const string& s, const string& w)
{
	vector<string> result;

	string copy = s;
	for (int i = 0; i < copy.size(); ++i)
	{
		for (int j = 0; j < w.size(); ++j)
			if (copy[i] == w[j])
				copy[i] = ' ';
	}

	return split(copy);
}

int main()
{
	vector<string> v;
	string temp;
	getline(cin, temp);
	v = split(temp, "chan");

	for (string x : v)
		cout << x << '\n';
}