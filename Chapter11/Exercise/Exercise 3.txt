void disemvowels(string fileName)
{
	ifstream ifile{ fileName };

	string result;
	char ch;
	while (ifile.get(ch))
	{
		if (isupper(ch)) ch = tolower(ch);

		switch (ch)
		{
		case 'a': case 'e': case 'i': case 'o': case 'u':
			break;
		default:
			result += ch;
			break;
		}
	}
	
	ofstream ofile{ fileName };
	ofile << result;

	ifile.close();
	ofile.close();
}
