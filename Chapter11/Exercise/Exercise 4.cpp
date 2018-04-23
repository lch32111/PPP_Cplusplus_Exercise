void multi_input()
{
	cout << "Write any number among base of octal, decimal, hexadecimal.\n"
		<< "And Press enter to see the result\n";

	
	vector<string> nv;
	vector<string> nexplanation;
	vector<int> dv;
	// the format is ..
	// nv nexplanation converts to number decimal 
	int input_MaxWidth{ 0 };

	// take all inputs and calculate max Width
	char ch;
	string st;
	while (cin.get(ch))
	{
		if (ch == ' ' || ch == '\n')
		{
			if (input_MaxWidth < st.size()) input_MaxWidth = st.size();
			nv.push_back(st);

			st.clear();

			if (ch == '\n')
				break;
		}
		else
		{
			st += ch;
		}
	}

	// calculate all inputs and calculate max width
	int explain_MaxWidth{ 0 };
	int decimal_MaxWidth{ 0 };
	for (string s : nv)
	{
		int decimalNumb;
		stringstream ss;

		if (s.at(0) == '0' && s.at(1) == 'x')
		{
			explain_MaxWidth = 11;

			// hexadecimal
			nexplanation.push_back("hexadecimal");

			ss << s;
			ss >> hex >> decimalNumb;

			ss << s;
			ss >> hex >> s;
			if (decimal_MaxWidth > s.size()) decimal_MaxWidth = s.size();


			dv.push_back(decimalNumb);
		}
		else if (s.at(0) == '0')
		{
			if (explain_MaxWidth == 0) // first time
				explain_MaxWidth = 5;

			// octal
			nexplanation.push_back("octal");

			ss << s;
			ss >> oct >> decimalNumb;
			
			ss << s;
			ss >> oct >> s;
			if (decimal_MaxWidth > s.size()) decimal_MaxWidth = s.size();

			dv.push_back(decimalNumb);
		}
		else
		{
			if (explain_MaxWidth <= 5) // octal or first time
				explain_MaxWidth = 7;

			// decimal
			nexplanation.push_back("decimal");

			ss << s;
			ss >> decimalNumb;

			if (decimal_MaxWidth > s.size()) decimal_MaxWidth = s.size();

			dv.push_back(decimalNumb);
		}
	}


	for (int i = 0; i < nv.size(); ++i)
	{
		cout << setw(input_MaxWidth) << nv[i] << ' '
			<< setw(explain_MaxWidth) << nexplanation[i] << ' '
			<< "converts to "
			<< setw(decimal_MaxWidth) << dv[i] << " decimal\n";
	}
}