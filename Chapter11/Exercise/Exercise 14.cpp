/*
14. Write a program that reads a text file and 
writes out how many characters of each character classification (11.6) are in the file.
*/

#include "std_lib_facilities.h"

vector<string> kindcharArray = 
{
	"whitespace", "alphabet", "hexadecimal",
	"uppercase", "lowercase", "control", "printable"
};

string kindofchar(char ch)
{
	string result;
	if (isspace(ch)) result += "whitespace";
	if (isalpha(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "alphabet";
	}
	if (isdigit(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "decimal";
	}
	if (isxdigit(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "hexadecimal";
	}
	if (isupper(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "uppercase";
	}
	if (islower(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "lowercase";
	}
	if (iscntrl(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "control";
	}
	if (isprint(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "printable";
	}

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

	stringstream ss(copy);
	string temp;
	while (ss >> temp)
		result.push_back(temp);

	return result;
}

int main()
{
	cout << "Enter the input file name to be reversed : ";
	string iname;
	cin >> iname;
	ifstream ifs{ iname };

	if (!ifs) error("can't open input file ", iname);

	char ch;
	vector<int> numberkind(kindcharArray.size(), 0);
	while (ifs.get(ch))
	{
		string result = kindofchar(ch);

		stringstream ss(result);
		vector<string> v = split(result, ",");


		for(int i = 0; i < v.size(); ++i)
			for (int j = 0; j < kindcharArray.size(); ++j)
			{
				if (v[i] == kindcharArray[j])
				{
					numberkind[j] += 1;
					break;
				}
			}
	}

	for (int i = 0; i < numberkind.size(); ++i)
	{
		cout << kindcharArray[i] << " letters : " << numberkind[i] << '\n';
	}


	ifs.close();

	return 0;
}