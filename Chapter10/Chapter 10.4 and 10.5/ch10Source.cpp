#include "ch10Source.h"
#include "Rational.h"

void end_of_loop(std::istream& ist, char term, const std::string& message)
{
	if (ist.fail()) // use term as terminator and/or separator
	{
		ist.clear();
		char ch;
		if (ist >> ch && ch == term) return; // all is fine
		error(message);
	}
}

void skip_to_int()
{
	if (std::cin.fail()) // we found something that wasn't an integer
	{
		std::cin.clear();  // we'd like to lookt at the characters
		for (char ch; std::cin >> ch;) // throw away non-digits
		{
			if (isdigit(ch) || ch == '-')
			{
				std::cin.unget(); // put the digit back, so that we can read the number
				return;
			}
		}
	}
	error("no input");  // eof or bad : give up
}

void skip_to_int(std::istream& is)
{
	if (is.fail()) // we found something that wasn't an integer
	{
		is.clear();  // we'd like to lookt at the characters
		for (char ch; is >> ch;) // throw away non-digits
		{
			if (isdigit(ch) || ch == '-')
			{
				is.unget(); // put the digit back, so that we can read the number
				return;
			}
		}
	}
	error("no input");  // eof or bad : give up
}

void find_next_int(std::istream& is)
{
	if (is.fail())
	{
		is.clear();
		for (char ch; is >> ch;)
		{
			if (isdigit(ch) || ch == '-')
			{
				is.unget();
				break;
			}
		}
	}
}

int get_int()
{
	int n = 0;
	while (true)
	{
		if (std::cin >> n) return n;
		std::cout << "Sorry, that was not a number; please try again\n";
		skip_to_int();
	}
}

int get_int(std::istream& is)
{
	int n = 0;
	while (true)
	{
		if (is >> n) return n;
		std::cout << "Sorry, that was not a number; please try again\n";
		skip_to_int(is);
	}
}

int get_int(int low, int high, const std::string& greeting, const std::string& sorry)
{
	std::cout << greeting << ": [" << low << ':' << high << "]\n";
	while (true)
	{
		int n = get_int();
		if (low <= n && n <= high) return n;
		std::cout << sorry << ": [" << low << ':' << high << "]\n";
	}
}

int month_to_int(const string& s)
// is s the name of a month? If so return its index [0:11] otherwise -1
{
	for (int i = 0; i < 12; ++i)
		if (month_input_tbl[i] == s)
			return i;
	return -1;
}

/* Temperature */
string int_to_month(const int& i)
{
	if (i < 0 || i >= 12) error("bad Month index\n");
	return month_print_tbl[i];
}

bool is_valid(const Reading& r)
// rough test
{
	if (r.day < 1 || 31 < r.day) return false;
	if (r.hour < 0 || 23 < r.hour) return false;
	if (r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}

double Celcius2F(const double c)
{
	return 1.8 * c + 32;
}

double F2Celcius(const double f)
{
	return  (f - 32.0) / 1.8;
}

ostream& print_years(ostream& os, const Year& y, const char mark)
// print years for console
{
	if (y.year < min_year || y.year > max_year) error("Bad Year Information\n");
	if (mark != celcius2f && mark != f2celcius &&
		mark != originalC && mark != originalF)
		error("Bad Temperature Representation Information\n");

	// Year
	os << "Year : " << y.year << '\n';

	// Month
	for (size_t i = 0; i < 12; ++i)
		if (y.month[i].month != not_a_month)
		{
			os << "\tMonth : " << int_to_month(y.month[i].month) << '\n';

			// Day
			for (size_t j = 1; j < 32; ++j)
				if (y.month[i].day[j].day != not_a_day)
				{
					os << "\t\tDay : " << j << '\n';

					// Hour
					for (size_t k = 0; k < 24; ++k)
						if (y.month[i].day[j].hour[k] != not_a_reading)
						{
							os << "\t\t\tHour : " << k << ", Temperature : ";
							
							if (mark == originalC)
								os << y.month[i].day[j].hour[k] << print_celcius << '\n';
							else if (mark == originalF)
								os << y.month[i].day[j].hour[k] << print_fahrenheit << '\n';
							else if (mark == f2celcius)
								os << F2Celcius(y.month[i].day[j].hour[k]) << print_celcius << '\n';
							else if (mark == celcius2f)
								os << Celcius2F(y.month[i].day[j].hour[k]) << print_fahrenheit << '\n';
						}
				}
		}

	return os;
}
/* Temperature */