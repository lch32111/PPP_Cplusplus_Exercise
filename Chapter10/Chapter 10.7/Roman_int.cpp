#include "Roman_int.h"

bool canRoman(string s)
{
	if (s.size() == 0) return false;
	
	for (size_t i = 0; i < s.size(); ++i)
		if (islower(s[i]))
			return false;

	return true;
}

bool canRoman(int v)
{
	if (v <= 0) return false;
	
	return true;
}

unsigned int Roman_char2int(const char c)
{
	for (size_t i = 0; i < Roman_tbl_size; ++i)
		if (Roman_char_tbl[i] == c)
			return Roman_int_tbl[i];

	error("Bad Roman Character\n");
	return 0;
}

char Roman_int2char(const unsigned int v)
{
	for (size_t i = 0; i < Roman_tbl_size; ++i)
		if (Roman_int_tbl[i] == v)
			return Roman_char_tbl[i];

	error("Bad Roman Int Measure\n");
	return NULL;
}

unsigned int Roman_string2int(const string& s)
{
	if (s.size() == 0) error("There's no character\n");
	if (s.size() == 1) return Roman_char2int(s[0]);

	unsigned int sum{ 0 };
	size_t s_index = s.size();
	unsigned int i{ 0 }; // index to take each character in s string.

	/* 
	Algorithm : Compare the first two character, and them
	if left is smaller than right, 
	the value of (right - left) will be added on the 'sum' variable, and
	the index will move next to the right ( index += 2)
	otherwise, only the left one is added on the 'sum', and the index will add just by one.
	*/
	while (i < s_index)
	{
		unsigned int left = Roman_char2int(s[i]);
		unsigned int right{ 0 };
		
		if(i + 1 < s_index)
			right = Roman_char2int(s[i + 1]);

		if (left < right)
		{
			sum += right - left;
			
			if (i != s_index - 1)
				i += 2;
		}
		else
		{
			sum += left;
			i += 1;
		}
	}

	return sum;
}

string Roman_int2string(const unsigned int v)
{
	if (v <= 0) error("Bad Roman number intializer", v);

	string result;
	result.reserve(30); // take enough capacity for string

	unsigned int rest = v;
	
	// the number more than 1000 should have multiple 'm'
	if (rest >= 1000)
	{
		int number = rest / 1000;

		for (int i = 0; i < number; ++i)
			result.push_back('m');
		
		rest -= number * 1000;
	}

	while (rest != 0)
	{
		unsigned int properNumber{ 0 };

		for (size_t i = 0; i < Roman_tbl_size; ++i)
		{
			if (rest >= Roman_int_tbl[i])
			{
				if (properNumber <= Roman_int_tbl[i])
					properNumber = Roman_int_tbl[i];
			}
		}

		result.push_back(Roman_int2char(properNumber));
		rest -= properNumber;
	}

	makeProperRomanString(result);
	return result;
}

void makeProperRomanString(string& out_s)
{
	// Case 900 dcccc -> cm
	// Case 90 lxxxx -> xc
	// Case 9  viiii -> ix
	
	// Case 400 cccc -> cd
	// Case 40 xxxx -> xl
	// Case 4 iiii -> iv
	
	for (size_t i = 0; i < out_s.size(); ++i)
	{
		if (i + 3 >= out_s.size())
			break;

		if (i + 4 < out_s.size())
		{
			for (size_t j = 0; j < 3; ++j)
			{
				if (compareLimitedString(out_s.c_str(), i, i + 4, Roman_longConvert_tbl[j]))
				{
					modifyString(out_s, i, i + 4, Roman_shortConver_tbl[j]);
				}
			}
		}

		if (i + 3 < out_s.size())
		{
			for (size_t k = 3; k < Roman_ctbl_size; ++k)
			{
				if (compareLimitedString(out_s.c_str(), i, i + 3, Roman_longConvert_tbl[k]))
				{
					modifyString(out_s, i, i + 3, Roman_shortConver_tbl[k]);
				}
			}
		}
	}
}

bool compareLimitedString(const char* s1, const int start, const int end, const string& value)
{
	char temp[20];
	int temp_size{ 0 };

	for (int i = start; i <= end; ++i)
	{
		temp[temp_size] = s1[i];
		++temp_size;
	}
	temp[temp_size] = '\0';

	return strcmp(temp, value.c_str()) == 0;
}

void modifyString(string& out_s, const int start, const int end, const string& value)
{
	int inputNumb = start;

	for (size_t i = 0; i < value.size(); ++i)
	{
		out_s[inputNumb] = value[i];
		++inputNumb;
	}

	out_s.erase(start + 2, end - inputNumb + 1);
}

ostream& operator<<(ostream& os, const Roman_int& r)
{
	return os << r.as_string();
}