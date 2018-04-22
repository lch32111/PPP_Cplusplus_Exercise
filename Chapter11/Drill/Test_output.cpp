#include "std_lib_facilities.h"

int main()
{
	int birth_year = 1234;
	cout << "dec : " << birth_year << '\t' 
		<< "hex : " << hex << birth_year << '\t' 
		<< "oct : " << oct << birth_year << '\n';
	int age = 26;
	cout << "dec : " << dec << age << '\t'
		<< "hex : " << hex << age << '\t'
		<< "oct : " << oct << age << '\n';

	cout << dec;

	int a, b, c, d;
	cin >> a >> oct >> b >> hex >> c >> d;
	// read a in decimal format, b in octal format, c and d in hex format with 1234. 
	cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
	// the result is 1234(dec) 668(1234oct->668dec) 4660(1234hex->4660dec) 4660

	// for this number, the fixed version is the most accurate representation.
	// because in this form, fixed can represent the point numbers within 6 digits.
	// So, unlike scientific representation rounding off a vlue, the fixed version shows the value directly.
	cout << 1234567.89 << '\t'
		<< fixed << 1234567.89 << '\t'
		<< scientific << 1234567.89 << '\n';

	vector<string> lastName;
	vector<string> firstName;
	vector<string> telephoneNumb;
	vector<string> emailAddress;

	int maxWidth{ 0 };
	int inputNumb{ 0 };
	cout << "Enter the number of input where you enter information : ";
	cin >> inputNumb;

	cout << "Enter the last name, first name, telephone number, email address of each one sequentailly\n";
	string temp;
	for (int i = 0; i < inputNumb; ++i)
	{
		cin >> temp;
		if (temp.size() > maxWidth) maxWidth = temp.size();
		lastName.push_back(temp);
		temp.clear();

		cin >> temp;
		if (temp.size() > maxWidth) maxWidth = temp.size();
		firstName.push_back(temp);
		temp.clear();

		cin >> temp;
		if (temp.size() > maxWidth) maxWidth = temp.size();
		telephoneNumb.push_back(temp);
		temp.clear();

		cin >> temp;
		if (temp.size() > maxWidth) maxWidth = temp.size();
		emailAddress.push_back(temp);
		temp.clear();
	}

	for (size_t i = 0; i < lastName.size(); ++i)
	{
		cout << setw(maxWidth) << lastName[i] << '|'
			<< setw(maxWidth) << firstName[i] << '|'
			<< setw(maxWidth) << telephoneNumb[i] << '|'
			<< setw(maxWidth) << emailAddress[i] << "|\n";
	}

}