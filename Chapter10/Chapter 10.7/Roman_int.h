#ifndef _ROMAN_INT_H_
#define _ROMAN_INT_H_

#include "std_lib_facilities.h"

bool canRoman(string s);
bool canRoman(int v);
unsigned int Roman_char2int(const char c);
char Roman_int2char(const unsigned int v);
unsigned int Roman_string2int(const string& s);
string Roman_int2string(const unsigned int v);
void makeProperRomanString(string& out_s);
bool compareLimitedString(const char* s1, const int start, const int end, const string& value);
void modifyString(string& out_s, const int start, const int end, const string& value);

class Roman_int
{
public:
	Roman_int(unsigned int value)
		: m_numberString(Roman_int2string(value)), m_number(value)
	{ }
	Roman_int(string s)
		: m_number(Roman_string2int(s)), m_numberString(s) { }
		
	int as_int() const { return m_number; }
	string as_string() const { return m_numberString; }
private:
	unsigned int m_number;
	string m_numberString;
};

ostream& operator<<(ostream& os, const Roman_int& r);

constexpr size_t Roman_tbl_size = 7;
const vector<char> Roman_char_tbl =
{
	'I', 'V', 'X', 'L', 'C', 'D', 'M'
};

const vector<unsigned int> Roman_int_tbl =
{
	1, 5, 10, 50, 100, 500, 1000
};

constexpr size_t Roman_ctbl_size = 6;
const vector<string> Roman_longConvert_tbl = 
{
	"DCCCC", "LXXXX", "VIIII", "CCCC", "XXXX", "IIII"
};

const vector<string> Roman_shortConver_tbl =
{
	"CM", "XC", "IX", "CD", "XL", "IV"
};

#endif