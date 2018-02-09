#ifndef _TEMP_STATS_H_
#define _TEMP_STATS_H_

#include "std_lib_facilities.h"
#include "ch10Source.h"

istream& operator>>(istream& is, Reading& r);
istream& operator>>(istream& is, Month& m);
istream& operator>>(istream& is, Year& y);
void readTempFile(istream& is, vector<Year>& y);

struct tempStats
{
	double mean;
	double median;
};

istream& readgetTempStats(istream& is, tempStats& ts, vector<Year>& y, char& mark);
istream& getYear(istream& is, Year& y, vector<double>& v);
istream& getMonth(istream& is, Month& m, vector<double>& v);
istream& getReading(istream& is, Reading& r, vector<double>& v);

#endif
