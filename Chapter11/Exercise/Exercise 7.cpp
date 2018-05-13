#include "std_lib_facilities.h"

vector<string> notString = 
{
	"ain t", "aren t", "isn t",
	"don t", "doesn t", "didn t",
	"hadn t", "haven t", "hasn t",
	"won t", "can t", "shouldn t"
};

vector<string> notchangeString =
{
	"am not", "are not", "is not",
	"do not", "does not", "did not",
	"had not", "have not", "has not",
	"will not", "can not", "should not"
};

class Punct_stream
	// like an istream, but the user can add to
{
public:
	Punct_stream(istream& is)
		:source{ is }, sensitive{ true } { }

	void whitespace(const string& s) // make s the whitespace set
	{
		white = s;
	}

	void add_white(char c) { white += c; } // add to the whitespace set
	bool is_whitespace(char c); // is c in the whitespace set?
	void case_sensitive(bool b) { sensitive = b; }
	bool is_case_sensitive() { return sensitive; }

	void changenotsentence(string& s);

	char get(char& c);
	Punct_stream& readlineWithhypen(string &s);
	Punct_stream& readline(string& s);
	Punct_stream& operator>>(string& s);
	operator bool();
private:
	istream& source; // character source
	istringstream buffer; // we let buffer do our formatting
	string white; // characters considered "whitespace"
	bool sensitive; // is the stream case-sensitive?
};

Punct_stream& Punct_stream::readlineWithhypen(string &s)
{
	while (!(getline(buffer, s)))
	{
		if (buffer.bad() || !source.good()) return *this;
		buffer.clear();

		string line;
		getline(source, line);

		for (int i = 0; i < line.size(); ++i)
		{
			if (is_whitespace(line[i]))
			{
				if (line[i] == '-')
				{
					if (i - 1 < 0 || i + 1 >= line.size())
						line[i] = ' ';
					else if (!isalpha(line[i - 1]) || !isalpha(line[i + 1]))
						line[i] = ' ';
				}
				else
					line[i] = ' ';
			}
			else if (!sensitive)
				line[i] = tolower(line[i]);
		}

		buffer.str(line);
	}

	return *this;
}

Punct_stream& Punct_stream::readline(string& s)
{
	while (!(getline(buffer, s)))
	{
		if (buffer.bad() || !source.good()) return *this;
		buffer.clear();

		string line;
		getline(source, line);

		for (char& ch : line)
			if (is_whitespace(ch))
				ch = ' '; // to space
			else if (!sensitive)
				ch = tolower(ch); // to lower case

		buffer.str(line);
	}

	return *this;
}

Punct_stream& Punct_stream::operator>>(string& s)
{
	while (!(buffer >> s)) // try to read from buffer
	{
		if (buffer.bad() || !source.good()) return *this;
		buffer.clear();

		string line;
		getline(source, line); // get a line from source

							   // do character replacement as needed:
		for (char& ch : line)
			if (is_whitespace(ch))
				ch = ' '; // to space
			else if (!sensitive)
				ch = tolower(ch); // to lower case

		buffer.str(line);
	}

	return *this;
}

char Punct_stream::get(char& c)
{
	while (!(buffer.get(c)))
	{
		if (buffer.bad() || !source.good()) return '\0';
		buffer.clear();

		string onechar;
		onechar += source.get();

		if (is_whitespace(onechar[0]))
			onechar[0] = ' ';
		else if (!sensitive)
			onechar[0] = tolower(onechar[0]);

		buffer.str(onechar);
	}

	return c;
}

bool Punct_stream::is_whitespace(char c)
{
	for (char w : white)
		if (c == w) return true;
	return false;
}

Punct_stream::operator bool()
{
	return !(source.fail() || source.bad()) && source.good();
}

void Punct_stream::changenotsentence(string &s)
{
	stringstream check(s);
    stringstream output;
	

	string leftword;
	string rightword;
	while (check >> leftword)
	{
		check >> rightword;

		if (check.eof() == false)
		{
			string result = leftword + ' ' + rightword;
			string expand;


			for (int i = 0; i < notString.size(); ++i)
			{
				if (result == notString[i])
				{
					expand = notchangeString[i];
					break;
				}
			}

			if (expand.size() == 0)
			{
				if (leftword.size() != 0)
					output << leftword << ' ';

				if (rightword.size() != 0)
					output << rightword << ' ';
			}
			else if (expand.size() >= 1)
				output << expand << ' ';
		}
		else
			output << leftword;
		
	}

	getline(output, s);
}

int main()
{
	Punct_stream ps{ cin };
	ps.case_sensitive(false);
	ps.whitespace("-.;,?\'"); // note \" means " in string

	string temp;
	ps.readlineWithhypen(temp);
	cout << temp << '\n';

	ps.changenotsentence(temp);
	cout << temp << '\n';
}