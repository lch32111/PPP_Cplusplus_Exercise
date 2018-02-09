#include "store_temps.h"

ostream& store_temp_inFile(ostream& os, const vector<Year>& y, const char mark)
// store the temperature in formatted file.
{
	if (mark != celcius2f && mark != f2celcius &&
		mark != originalC && mark != originalF)
		error("Bad Temperature Representation Information\n");
	else
		os << "Representation " << char_fileprint_representation(mark) << newline;

	for (size_t i = 0; i < y.size(); ++i)
	{
		if (y[i].year < min_year || y[i].year > max_year) error("Bad Year Information\n");
		else
			store_year(os, y[i], mark);
	}

	return os;
}

ostream& store_year(ostream& os, const Year& y, const char mark)
{
	// Year
	os << Open_Year_Parenthesis << space;
	os << "year " << y.year << space;

	// Month Valid Check
	int number_month = 0;
	for (size_t i = 0; i < 12; ++i)
		if (y.month[i].month != not_a_month)
		{
			++number_month;
			break;
		}

	if (number_month == 0)
		// There is no month. it means no Temperature Data in year
		goto end;
	else
	{
		os << newline;

		for (size_t i = 0; i < 12; ++i)
		{
			if (y.month[i].month != not_a_month)
			{
				os << tab << Open_Month_Parenthesis << space;
				store_month(os, y.month[i], mark);
				os << End_Month_Parenthesis << newline;
			}
		}
	}
end:
	os << End_Year_Parenthesis << newline;
	return os;
}

ostream& store_month(ostream& os, const Month& m, const char mark)
// store month in formatted file, chained with store_temp_inFile
{
	if (m.month < 0 || m.month >= 12) error("Bad Month Information\n");
	
	os << "month" << space << int_fileprint_month(m.month) << space;

	// Day Valid Check
	int number_day = 0;
	for (size_t i = 1; i < 32; ++i)
		if (m.day[i].day != not_a_day)
		{
			++number_day;
			break;
		}

	if (number_day == 0)
	// There is no day. it means no Temperature Data in month
		goto end;
	else
	{
		// Day
		for (size_t i = 1; i < 32; ++i)
		{
			if (m.day[i].day != not_a_day)
				store_day(os, m.day[i], mark);
		}
	}

end:
	return os;
}

ostream& store_day(ostream& os, const Day& d, const char mark)
// store day in formatted file, chained with store_month
{
	if (d.day < 1 || d.day >= 32) error("Bad Day Information\n");

	// Don't need to check hour. 
	// if d. day is valid, there is temperature data in day
	
	// Hour
	for(size_t i = 0; i < 24; ++i)
		if (d.hour[i] != not_a_reading)
		{
			os << Open_Temperature_Parenthesis;
			os << d.day << space << i << space;  // Day Hour 
			
			// Tempearture
			if (mark == originalC || mark == originalF)
				os << d.hour[i];
			else if (mark == celcius2f)
				os << Celcius2F(d.hour[i]);
			else if (mark == f2celcius)
				os << F2Celcius(d.hour[i]);

			os << End_Temperature_Parenthesis << space;
		}

	return os;
}

string char_fileprint_representation(const char mark)
{
	if (mark == originalC || mark == f2celcius)
		return print_celcius;
	else if (mark == originalF || mark == celcius2f)
		return print_fahrenheit;
	
	error("Bad Temperature Representation Information");
	return NULL;
}

string int_fileprint_month(const int& i)
// return string month for file print
{
	if (i < 0 || i >= 12) error("bad Month index\n");
	return month_input_tbl[i];
}