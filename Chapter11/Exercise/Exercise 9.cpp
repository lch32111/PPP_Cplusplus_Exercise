#include "std_lib_facilities.h"

int main()
{
	cout << "Please enter input file name(text2binary) : ";
	string iname;
	cin >> iname;
	ifstream ifs{ iname };
	if (!ifs) error("can't open input file ", iname);

	cout << "Please enter output file name(text2binary) : ";
	string oname;
	cin >> oname;
	ofstream ofs{ oname, ios_base::binary };
	if (!ofs) error("can't open output file ", oname);

	char ch;
	while (ifs.get(ch))
	{
		ofs.write(as_bytes(ch), sizeof(char));
	}

	ifs.close();
	ofs.close();


	cout << "Please enter input file name(binary2text) : ";
	cin >> iname;
	ifs.open(iname, ios_base::binary);
	if (!ifs) error("can't open input file ", iname);

	cout << "Please enter ouput file name (binary2text) : ";
	cin >> oname;
	ofs.open(oname);
	
	while (ifs.read(as_bytes(ch), sizeof(char)))
	{
		ofs << ch;
	}

	ifs.close();
	ofs.close();
}