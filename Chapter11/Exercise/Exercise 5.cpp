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
		result += "decimal digit";
	}
	if (isxdigit(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "hexadecimal digit";
	}
	if (isupper(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "uppercase letter";
	}
	if (islower(ch)) 
	{
		if (result.size() != 0)
			result += ", ";
		result += "lowercase letter";
	}
	if (iscntrl(ch)) 
	{
		if (result.size() != 0)
			result += ", ";
		result += "control character";
	}
	if (isprint(ch))
	{
		if (result.size() != 0)
			result += ", ";
		result += "printable character";
	}

	return result;
}

void evaluateChar(string charlist)
{
	cout << "Evaluating \"" << charlist << "\"\n";

	for (size_t i = 0; i < charlist.size(); ++i)
		cout << '\'' << charlist[i] << "\' is "<< kindofchar(charlist[i]) << '\n';
}

int main()
{
	evaluateChar("Hi there!");
}