#include "std_lib_facilities.h"

vector<string> notString = 
{
	"ain t", "aren t", "isn t", "wasn t", "weren t",
	"don t", "doesn t", "didn t",
	"hadn t", "haven t", "hasn t",
	"won t", "can t", "shouldn t"
};

vector<string> notchangeString =
{
	"am not", "are not", "is not", "was not", "were not",
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
	
	vector<string> words;
	string temp;
	while (check >> temp)
		words.push_back(temp);

	string leftword;
	string rightword;
	for (int i = 0; i < words.size() - 1; ++i)
	{
		leftword = words[i];
		rightword = words[i + 1];

		for(int j = 0; j < notString.size(); ++j)
			if (leftword + ' ' + rightword == notString[j])
			{
				stringstream ss;
				ss << notchangeString[j];

				string front, back;
				ss >> front >> back;

				words[i] = front;
				words[i + 1] = back;
			}
	}

	for (int i = 0; i < words.size(); ++i)
	{
		output << words[i];

		if (i != words.size() - 1)
			output << ' ';
	}

	getline(output, s);
}

int main()
{
	string address;
	ifstream infile;
	ofstream outfile;

	cout << "Enter the input file address : ";
	cin >> address;
	infile.open(address);
	cout << "Enter the output file address : ";
	cin >> address;
	outfile.open(address);

	if (!infile || !outfile)
		cerr << "Something error happend in opening file\n";

	Punct_stream ps{ infile };
	ps.case_sensitive(false);
	ps.whitespace("-.:();,?\'"); 

	vector<string> dictionary;
	string temp;
	while (ps.readlineWithhypen(temp))
	{
		ps.changenotsentence(temp);

		stringstream ss;
		ss << temp;

		string temp2;
		while (ss >> temp2)
			dictionary.push_back(temp2);
	}
	sort(dictionary.begin(), dictionary.end());

	for (int i = 0; i < dictionary.size(); ++i)
		if (i == 0 || dictionary[i] != dictionary[i - 1])
			outfile << dictionary[i] << '\n';

	infile.close();
	outfile.close();
}