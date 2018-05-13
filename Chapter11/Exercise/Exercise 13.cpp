/*
13. Reverse the order of words (defined as whitespace-separated strings) in a file.
For example, Norwegian Blue parrot becomes parrot Blue Norwegian.
You are allowed to assume that all the strings from the file will fit into memory at once.
*/

#include "std_lib_facilities.h"

int main()
{
	cout << "Enter the input file name to be reversed : ";
	string iname;
	cin >> iname;
	ifstream ifs{ iname };

	if (!ifs) error("can't open input file ", iname);

	cout << " ENther the output file name with the reversed text : ";
	string oname;
	cin >> oname;
	ofstream ofs{ oname };

	if (!ofs) error("can't open output file ", oname);

	vector<string> v;
	string temp;
	while (ifs >> temp)
		v.push_back(temp);

	for (int i = v.size() - 1; i >= 0; --i)
	{
		ofs << v[i];
		if (i != 0)
			ofs << ' ';
	}

	ifs.close();
	ofs.close();

	return 0;
}