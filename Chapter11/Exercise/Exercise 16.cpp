/*
16. Write a program to read a file of whitespace-separated numbers 
and output them in order (lowest value first), one value per line. 
Write a value only once, and if it occurs more than once 
write the count of its occurrences on its line. For example, 7 5 5 7 3 1175 5 should give
3
5 3
7 2
117
*/

#include "std_lib_facilities.h"

int main()
{
	cout << "Enter the input file name : ";
	string iname;
	cin >> iname;
	ifstream ifs{ iname };

	if (!ifs) error("can't open input file ", iname);

	vector<int> v;
	int x;

	while (ifs >> x)
		v.push_back(x);
	
	sort(v.begin(), v.end());

	int rep{ 0 };
	for (int i = 0; i < v.size(); ++i)
	{
		if (i == 0 || v[i] != v[i - 1])
		{
			if (rep > 1) cout << "\t" << rep;
			cout << '\n';
			rep = 1;
			cout << v[i];
		}
		else
			++rep;

		if (i == v.size() - 1 && rep > 1)
			cout << '\t' << rep << '\n';
	}
	

	ifs.close();

	return 0;
}