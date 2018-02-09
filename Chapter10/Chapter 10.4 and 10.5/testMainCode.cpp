#include "std_lib_facilities.h"
#include "ch10Source.h"
#include "store_temps.h"
#include "temp_stats.h"

int main()
{
	try
	{
		vector<Year> test;
		tempStats stats;
		char mark;

		ifstream ifst("Changed_temps.txt");
		readgetTempStats(ifst, stats, test, mark);
		ifst.close();

		cout << "Temperature mean : " << stats.mean << '\n';
		cout << "Temperature median : " << stats.median << '\n';

		for (size_t i = 0; i < test.size(); ++i)
			print_years(cout, test[i], mark);

		for (size_t i = 0; i < test.size(); ++i)
			print_years(cout, test[i], celcius2f);
	}
	catch (exception& e)
	{
		cerr << e.what() << '\n';
	}
}