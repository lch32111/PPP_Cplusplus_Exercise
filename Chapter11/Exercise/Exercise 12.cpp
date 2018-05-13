/*
12. Reverse the order of characters in a text file. For example, asdfghjkl becomes lkjhgfdsa. 
Warning: There is no really good, portable, and efficient way of reading a file backward.
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

	vector<char> v;
	char ch;
	while (ifs.get(ch))
		v.push_back(ch);

	for (int i = v.size() - 1; i >= 0; --i)
		ofs << v[i];

	ifs.close();
	ofs.close();

	return 0;
}