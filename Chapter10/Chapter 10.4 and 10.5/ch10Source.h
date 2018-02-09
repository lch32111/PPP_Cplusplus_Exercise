#ifndef _CH_10_SOURCE_H_
#define _CH_10_SOURCE_H_

#include "std_lib_facilities.h"

void end_of_loop(std::istream& ist, char term, const std::string& message);
void skip_to_int();
void skip_to_int(std::istream& is);
void find_next_int(std::istream& is);
int get_int();
int get_int(std::istream& is);
int get_int(int low, int high, const std::string& greeting, const std::string& sorry);

/* Temperature */
const int not_a_reading = -7777;
const int not_a_day = -30;
const int not_a_month = -1;

constexpr int min_year = 1850;
constexpr int max_year = 2019;
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

constexpr char celcius2f = 'f';
constexpr char f2celcius = 'c';
constexpr char originalC = 'o';
constexpr char originalF = 'p';
const string fileprint_celcius = "Celcius";
const string fileprint_fahrenheit = "Fahrenheit";
const string print_celcius = "'C";
const string print_fahrenheit = "'F";

const vector<string> month_input_tbl =
{
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"
};

const vector<string> month_print_tbl =
{
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

struct Reading
{
	int day;
	int hour;
	double temperature;
};

struct Day
{
	int day{ not_a_day }; // [1:31] 
	vector<double> hour{ vector<double>(24, not_a_reading) };
};

struct Month // a month of temperature readings
{
	int month{ not_a_month }; // [0:11] January is 0
	vector<Day> day{ 32 }; // [1:31] one vector of readings per day
};

struct Year // a year of temperature readings organized by month
{
	int year; // positive == A.D.
	vector<Month> month{ 12 }; // [0:11] January is 0
};

int month_to_int(const string& s);
string int_to_month(const int& i);
bool is_valid(const Reading& r);
double Celcius2F(const double c);
double F2Celcius(const double f);
ostream& print_years(ostream& os, const Year& y, const char mark);
/* Temperature */

#endif

