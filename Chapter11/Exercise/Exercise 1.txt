void file2Lowercase()
{
	cout << "Enter the file name, where you want to convert its input to all lower case\n";

	string fiName;
	string foName = "lower ";

	cin >> fiName;
	foName += fiName;

	ifstream originFile{ fiName };
	ofstream newFile{ foName };

	char ch;
	while (originFile.get(ch))
	{
		if (isupper(ch)) ch = tolower(ch);
		newFile << ch;
	}
	
	originFile.close();
	newFile.close();
}