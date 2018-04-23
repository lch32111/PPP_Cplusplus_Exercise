#include "std_lib_facilities.h"

void printfilewith(string fileName, string word)
{
	ifstream file{ fileName };

	string readed;

	int lineIndex{ 0 };
	while (getline(file, readed))
	{
		++lineIndex;
		cout << lineIndex << ' ' << word << ' ' << readed << '\n';
	}

	file.close();
}

int main()
{
	printfilewith("result.txt", "test");
}