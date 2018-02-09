#include "temp_stats.h"

/* Temperature Reading */
istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r
// format: (3 4 9.7)
// check format, but don't bother with data validity
{
	char ch1;
	if (is >> ch1 && ch1 != '(') // could it be a Rdading
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char ch2;
	int d;
	int h;
	double t;

	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') error("bad reading"); // messed-up reading
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

istream& operator>>(istream& is, Month& m)
// read a month from is into m
// format : ( month feb . . .}
{
	char ch = 0;
	if (is >> ch && ch != '{')
	{
		is.unget();
		is.clear(ios_base::failbit); // we failed to read a Month
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error("bad start of month");
	m.month = month_to_int(mm);
	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r;)
	{
		if (is_valid(r))
		{
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;

			m.day[r.day].hour[r.hour] = r.temperature;
			m.day[r.day].day = r.day;
		}
		else
			++invalids;
	}

	if (invalids) error("invalid readings in month", invalids);
	if (duplicates) error("duplicate readings in month", duplicates);
	end_of_loop(is, '}', "bad end of month");

	return is;
}

istream& operator>>(istream& is, Year& y)
// read a year from is into y
// format : { year 1972 . . .}
{
	char ch;
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year") error("bad start of year");
	y.year = yy;

	while (true)
	{
		Month m;
		if (!(is >> m)) break;
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}

void readTempFile(istream& is, vector<Year>& y)
{
	while (true)
	{
		Year tempY;
		if (is >> tempY) y.push_back(tempY);
		else
			break;
	}
}


/* Temperature Reading */

/* Get Temp Stats*/
istream& readgetTempStats(istream& is, tempStats& ts, vector<Year>& y, char& mark)
{
	vector<double> tempVector;

	string r;
	string Rmark;
	is >> r >> Rmark;
	if (r != "Representation")
		error("Bad Representation Information\n");
	if (Rmark == fileprint_celcius)
		mark = originalC;
	else if (Rmark == fileprint_fahrenheit)
		mark = originalF;
	else
		error("Bad Representation Informaton\n");


	while (true)
	{
		Year tempY;
		if (getYear(is, tempY, tempVector)) { y.push_back(tempY); }
		else break;
	}

	double sum = 0.f;
	for (size_t i = 0; i < tempVector.size(); ++i)
		sum += tempVector[i];

	ts.mean = sum / tempVector.size();
	ts.median = tempVector[tempVector.size() / 2];

	return is;
}

istream& getYear(istream& is, Year& y, vector<double>& v)
{
	char ch;
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year") error("bad start of year");
	y.year = yy;

	while (true)
	{
		Month m;
		if (!getMonth(is, m, v)) break;
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}

istream& getMonth(istream& is, Month& m, vector<double>& v)
{
	char ch = 0;
	if (is >> ch && ch != '{')
	{
		is.unget();
		is.clear(ios_base::failbit); // we failed to read a Month
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error("bad start of month");
	m.month = month_to_int(mm);
	int duplicates = 0;
	int invalids = 0;
	for (Reading r; getReading(is, r, v);)
	{
		if (is_valid(r))
		{
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;

			m.day[r.day].hour[r.hour] = r.temperature;
			m.day[r.day].day = r.day;
		}
		else
			++invalids;
	}

	if (invalids) error("invalid readings in month", invalids);
	if (duplicates) error("duplicate readings in month", duplicates);
	end_of_loop(is, '}', "bad end of month");

	return is;
}

istream& getReading(istream& is, Reading& r, vector<double>& v)
{
	char ch1;
	if (is >> ch1 && ch1 != '(') // could it be a Rdading
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char ch2;
	int d;
	int h;
	double t;

	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') error("bad reading"); // messed-up reading
	r.day = d;
	r.hour = h;
	r.temperature = t;
	v.push_back(t); // !!
	return is;
}

/* Get Temp Stats*/